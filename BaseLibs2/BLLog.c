#include "stdafx.h"
#include "BLArray.h"
#include "BLString.h"
#include "BLStringBuilder.h"
#include "BLError.h"
#include "BLLog.h"
#include "BLWinPath.h"

const wchar_t* BLLogIniKeys[] = {
	L"path",
	L"level",
	L"trigger",
	L"bufsize",
	L"filesize",
	L"rolling"
};

const wchar_t* BLLogIniSections[] = {
	L"log"
};

#define MAX_PATH_1 (MAX_PATH - 1)
#define MAX_PATH_2 (MAX_PATH - 2)
#define READINI_ERROR_BREAK(valLen,err) \
if ((valLen == MAX_PATH_1) || (valLen == MAX_PATH_2)) { \
	err = ERROR_INSUFFICIENT_BUFFER; break; \
} else if (valLen == 0) { \
	err = ERROR_BAD_FORMAT; break; \
}

#define READINI_INT_ERROR_BREAK(intVal,intValLimit,err) \
if (intVal >= intValLimit) { \
	err = ERROR_BAD_FORMAT; break; \
}

#define READINI_INT_ZERO_ERROR_BREAK(intVal, err) \
if (intVal == 0) { \
	err = ERROR_BAD_FORMAT; break; \
}

DWORD BLLogIni_Read(PBLLogIni * pp, const wchar_t * iniFilePath)
{
	DWORD err = ERROR_SUCCESS;
	wchar_t buf[MAX_PATH];
	const DWORD maxPath_1 = MAX_PATH - 1;
	const DWORD maxPath_2 = MAX_PATH - 2;
	do {
		BLLogIni_Delete(pp);
		PBLLogIni p = *pp = (PBLLogIni)malloc(sizeof(BLLogIni));
		p->filePath = NULL;
		const wchar_t* sec = BLLogIniSections[BLLogIniSec_log];
		const wchar_t* key = BLLogIniKeys[BLLogIniItem_path];
		DWORD strValLen = GetPrivateProfileString(
			sec, key, NULL, buf, (DWORD)MAX_PATH, iniFilePath);
		READINI_ERROR_BREAK(strValLen, err);
		p->filePath = BLString_NewW(buf, 0);

		key = BLLogIniKeys[BLLogIniItem_level];
		p->ll = (BLLogLevel)GetPrivateProfileInt(
			sec, key, (INT)BLLogLevel_Invalid, iniFilePath
		);
		READINI_INT_ERROR_BREAK((INT)(p->ll), (INT)BLLogLevel_Invalid, err);
		
		key = BLLogIniKeys[BLLogIniItem_trigger];
		p->lwt = (BLLogWriteTrigger)GetPrivateProfileInt(
			sec, key, (INT)BLLogWriteTrigger_Invalid, iniFilePath
		);
		READINI_INT_ERROR_BREAK((INT)(p->lwt), (INT)BLLogWriteTrigger_Invalid, err);

		key = BLLogIniKeys[BLLogIniItem_bufsize];
		p->cbBuf = GetPrivateProfileInt(sec, key, 0, iniFilePath);
		READINI_INT_ZERO_ERROR_BREAK(p->cbBuf, err);
		
		key = BLLogIniKeys[BLLogIniItem_filesize];
		p->cbFile = GetPrivateProfileInt(sec, key, 0, iniFilePath);
		READINI_INT_ZERO_ERROR_BREAK(p->cbFile, err);

		key = BLLogIniKeys[BLLogIniItem_rolling];
		p->cFiles = GetPrivateProfileInt(sec, key, BLLOG_ROLLING_MAX, iniFilePath);
		READINI_INT_ERROR_BREAK(p->cFiles, BLLOG_ROLLING_MAX, err);
	} while (false);
	BLLogIni_Delete(pp);
	return err;
}

void BLLogIni_Delete(PBLLogIni * pp)
{
	if (*pp)
	{
		BLArray_Delete(&((*pp)->filePath));
		free(*pp);
		*pp = NULL;
	}
}

PBLLogIni BLLogIni_Dup(PCBLLogIni p)
{
	size_t cbAlloc = sizeof(BLLogIni);
	PBLLogIni pNew = (PBLLogIni)malloc(cbAlloc);
	memcpy_s(pNew, cbAlloc, p, sizeof(BLLogIni));
	pNew->filePath = BLString_NewW(p->filePath->data.wc, 0);
	return pNew;
}

#define IF_NULL_ERROR_BREAK(p,err) \
if (p == NULL) { \
	err = ERROR_NOT_ENOUGH_MEMORY; break; \
}

DWORD BLLog_New(PBLLog * pp, PCBLLogIni ini, const wchar_t* *modNameCandidates)
{
	DWORD err = ERROR_SUCCESS;
	PBLArray moduleFilePath = NULL;
	do {
		PBLLog p = (PBLLog)malloc(sizeof(BLLog));
		IF_NULL_ERROR_BREAK(p, err);
		p->ini = BLLogIni_Dup(ini);
		IF_NULL_ERROR_BREAK(p, err);

		// check log file write permission and folder existence
		if ((err = BLWinPath_CanWrite(p->ini->filePath->data.wc)) != ERROR_SUCCESS)
		{
			break;
		}

		// initialize critical section
		InitializeCriticalSection(&(p->cs));

		// get module filename
		moduleFilePath = BLWinPath_GetModulePath(modNameCandidates);
		p->moduleName = BLString_NewW(PathFindFileName(moduleFilePath->data.wc), 0);

		// get process ID
		p->processId = GetCurrentProcessId();

		p->iBuf = 0;

		p->buf[0] = BLBuffer_New(ini->cbBuf, BLType_c);
		p->buf[1] = BLBuffer_New(ini->cbBuf, BLType_c);
		*pp = p;
	} while (false);
	if (err)
	{
		BLLog_Delete(pp);
	}
	BLArray_Delete(&moduleFilePath);
	return err;
}

void BLLog_Delete(PBLLog * pp)
{
	if (*pp)
	{
		DeleteCriticalSection(&(*pp)->cs);
		BLArray_Delte(&((*pp)->moduleName));
		BLLogIni_Delete(&((*pp)->ini));
		BLBuffer_Delete(&((*pp)->buf[0]));
		BLBuffer_Delete(&((*pp)->buf[1]));
		free(*pp);
		*pp = NULL;
	}
}

void BLLog_AppendHeader(PBLLog p, BLWriteBuffer *wb)
{
	static SYSTEMTIME st;
	GetSystemTime(&st);
	int iWritten = _snwprinitf_s(wb->pwc, wb->ccLen, wb->ccLen - 1,
		BLLOG_HEADER_FORMAT_DESCRIPTOR,
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
		(int)(p->ini->ll), p->moduleName->data.wc, p->processId
	);
	if (0 < iWritten && iWritten < wb->ccLen)
	{
		wb->ccLen -= iWritten;
		wb->pwc += iWritten;
	}
}

BLWriteBuffer BLLog_Get(PBLLog p)
{
	BLWriteBuffer wb = { 0 };
	EnterCriticalSection(&(p->cs));
	wb.ccLen = (p->buf[p->iBuf]->arrayData.end.wc) - (p->buf[p->iBuf]->putter.wc);
	wb.pwc = (p->buf[p->iBuf]->putter.wc);
	if (wb.ccLen < (BLLOG_HEADER_LENGTH(p->moduleName->data.wc) + 2 * MAX_PATH))
	{
		p->iBuf++;
		p->iBuf &= 1;
		if (p->iBuf == 0)
		{ // buffer full
			if (p->ini->lwt == BLLogWriteTrigger_BufferFull)
			{
				if (BLLog_Flush(p))
				{
					wb.ccLen = 0;
					wb.pwc = NULL;
					return wb;
				}
			}
			else
			{
				BLBuffer_Clear(p->buf[p->iBuf]);
				wb.ccLen = (p->buf[p->iBuf]->arrayData.end.wc) - (p->buf[p->iBuf]->putter.wc);
				wb.pwc = (p->buf[p->iBuf]->putter.wc);
			}
		}
	}

	return wb;
}

DWORD BLLog_Release(PBLLog p, BLWriteBuffer writeBuffer)
{
	DWORD err = ERROR_SUCCESS;
	do {
		if (writeBuffer.pwc - p->buf[p->iBuf] > 0)
		{
			err = ERROR_INVALID_OPERATION; break;
		}

	} while (false);
	LeaveCriticalSection(&(p->cs));
	return err;
}

