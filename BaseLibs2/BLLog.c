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
		BLArray_Delete(&((*pp)->moduleName));
		BLLogIni_Delete(&((*pp)->ini));
		BLBuffer_Delete(&((*pp)->buf[0]));
		BLBuffer_Delete(&((*pp)->buf[1]));
		free(*pp);
		*pp = NULL;
	}
}

/*
This is private to BLLog.c.
Fill wb with header info; date-time, log level, module name, and process id.
*/
void _BLLog_FillHeader(PBLLog p, PBLWriteBuffer wb)
{
	static SYSTEMTIME st;
	GetSystemTime(&st);
	int iWritten = _snwprintf_s(wb->pwc, wb->ccLen, wb->ccLen - 1,
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

/*
Append the contents in wb to BLLog internal buffer.
*/
DWORD _BLLog_AppendBuffer(PBLLog p, BLWriteBuffer *wb)
{

}

/*
Flush buffer always
*/
DWORD _BLLog_FlushBuffer(PBLLog p)
{

}

/*
Roll files always
*/
DWORD _BLLog_RollFilesAlways(PBLLog p)
{
	const wchar_t* basePath = p->ini->filePath->data.wc;
	size_t ccBase = wcslen(basePath);
	size_t ccMargin = 4;
	size_t ccMaxPathLen = ccBase + ccMargin;
	PBLArray srcPath = BLArray_New(ccMaxPathLen, BLType_wc);
	PBLArray dstPath = BLArray_New(ccMaxPathLen, BLType_wc);
	DWORD err = ERROR_SUCCESS;
	do {
		size_t iter = p->ini->cFiles;
		while (iter)
		{
			// create destination path name
			wcscpy_s(dstPath->data.wc, dstPath->end.wc - dstPath->data.wc, basePath);
			wchar_t* wrptr = dstPath->data.wc + ccBase;
			_snwprintf_s(wrptr, ccMargin, ccMargin - 1, L"%03zu", iter--);
				// create the destination path and decrement iteration counter.

			// create source path name
			wcscpy_s(srcPath->data.wc, srcPath->end.wc - srcPath->data.wc, basePath);
			if (iter)
			{
				wrptr = srcPath->data.wc + ccBase;
				_snwprintf_s(wrptr, ccMargin, ccMargin - 1, L"%03zu", iter);
			}

			// delete destination file if exists.
			if (PathFileExists(dstPath->data.wc))
			{
				if (!DeleteFile(dstPath->data.wc))
				{
					err = GetLastError(); break;
				}
			}
			// move the source file.
			if (!MoveFile(srcPath->data.wc, dstPath->data.wc))
			{
				err = GetLastError(); break;
			}
		}
	} while (false);
	BLArray_Delete(&srcPath);
	BLArray_Delete(&dstPath);
	return err;
}

/*
Roll file if file rolling mode is selected and file size exceeds the limit.
*/
DWORD _BLLog_RollFiles(PBLLog p)
{
	DWORD err = ERROR_SUCCESS;
	do {
		// get the target file size
		HANDLE h = CreateFile(p->ini->filePath->data.wc, GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h == INVALID_HANDLE_VALUE)
		{
			err = GetLastError();
			break;
		}

		DWORD cbFile = GetFileSize(h, NULL);
		CloseHandle(h);

		if (cbFile > p->ini->cbFile)
		{
			err = _BLLog_RollFilesAlways(p);
		}
	} while (false);
	return err;
}

/*
Flush currently selected internal buffer automatically.
*/
DWORD _BLLog_AutoFlush(PBLLog p)
{
	DWORD err = ERROR_SUCCESS;
	do {

	} while (false);
	return err;
}

DWORD BLLog_Get(PBLLog p, PBLWriteBuffer wb)
{
	DWORD err = ERROR_SUCCESS;
	do {

	} while (false);
	return err;
}


DWORD BLLog_GetAnother(PBLLog p, PBLWriteBuffer wb)
{
	
}


DWORD BLLog_Release(PBLLog p, BLWriteBuffer writeBuffer)
{
	DWORD err = ERROR_SUCCESS;
	do {
		if (writeBuffer.pwc - p->buf[p->iBuf]->arrayData.data.wc > 0)
		{
			err = ERROR_INVALID_OPERATION; break;
		}

	} while (false);
	LeaveCriticalSection(&(p->cs));
	return err;
}

