#include "stdafx.h"
#include "BLError.h"
#include "BLArray.h"
#include "BLString.h"
#include "BLLog.h"
#include "BLWinPath.h"

const wchar_t* BLLogType_Labels[] = {
	L"BLLogType_c",
	L"BLLogType_wc",
	L"BLLogType_i8",
	L"BLLogType_i16",
	L"BLLogType_i32",
	L"BLLogType_i64",
	L"BLLogType_ui8",
	L"BLLogType_ui16",
	L"BLLogType_ui32",
	L"BLLogType_ui64",
	L"BLLogType_f",
	L"BLLogType_d",
	L"BLLogType_fc",
	L"BLLogType_dc",
	L"BLLogType_ptr",
	L"BLLogType_Array_c",
	L"BLLogType_Array_wc",
	L"BLLogType_Array_i8",
	L"BLLogType_Array_i16",
	L"BLLogType_Array_i32",
	L"BLLogType_Array_i64",
	L"BLLogType_Array_ui8",
	L"BLLogType_Array_ui16",
	L"BLLogType_Array_ui32",
	L"BLLogType_Array_ui64",
	L"BLLogType_Array_f",
	L"BLLogType_Array_d",
	L"BLLogType_Array_fc",
	L"BLLogType_Array_dc",
	L"BLLogType_Array_ptr"
};

DWORD _BLLogger_OpenAppend(PBLLogWriter writer)
{
	DWORD err = ERROR_SUCCESS;
	do {
		writer->file.hFile = CreateFile(writer->filePath->data.wc, FILE_APPEND_DATA, 0,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == writer->file.hFile)
		{
			err = GetLastError(); break;
		}
	} while (false);
	return err;
}

DWORD _BLLogger_OpenCreate(PBLLogWriter writer)
{
	static const wchar_t headline[] = L"\xfefftime(s),time(ns),PID,TID,PRJ_ID,SRC_ID,SRC_LINE,Data type,Error type,Error code,Data\r\n";
	DWORD err = ERROR_SUCCESS;
	do {
		writer->file.hFile = CreateFile(writer->filePath->data.wc, GENERIC_WRITE, 0,
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == writer->file.hFile)
		{
			err = GetLastError(); break;
		}
		if (!WriteFile(writer->file.hFile, headline, sizeof(headline) - 2, &err, NULL))
		{
			err = GetLastError(); break;
		}
	} while (false);
	if (err && writer->file.hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(writer->file.hFile);
		writer->file.hFile = INVALID_HANDLE_VALUE;
	}
	return err;
}
BLError BLLogger_New(const wchar_t * filePath, size_t cRecord, BLLogMode logMode, const wchar_t * proj_name, PBLLogger * ppLogger)
{
	BLError err = BLError_MakeWin(ERROR_SUCCESS);
	do {
		// check parent folder existence and write permission of the log file
		if (ERROR_SUCCESS != (err.u = BLWinPath_CanWrite(filePath)))
		{
			break;
		}
		
		if (logMode != BLLogMode_AFCO)
		{
			err.u = ERROR_INVALID_OPERATION; break;
		}

		if (*ppLogger)
		{
			BLLogger_Delete(ppLogger);
		}
		size_t cbAlloc = sizeof(BLLogger) + cRecord * sizeof(BLLogData);
		PBLLogger logger = (*ppLogger) = (PBLLogger)malloc(cbAlloc);
		logger->wrptr = (PBLLogData)(logger + 1);
		logger->end = (PBLLogData)(((uint8_t*)logger) + cbAlloc);
		// fill header template
		logger->header.time.tv_nsec = 0;
		logger->header.time.tv_sec = 0;
		logger->header.pid = GetCurrentProcessId();
		logger->header.tid = GetThreadId(GetCurrentThread());
		logger->header.proj_id = BLString_Hash16raw(proj_name);
		logger->header.src_id = logger->header.src_line = 0;
		logger->header.type = BLLogType_c;
		logger->writer.filePath = BLString_NewW(filePath, 0);
		if (logMode == BLLogMode_AFCO)
		{
			if (PathFileExists(filePath))
			{
				err.u = _BLLogger_OpenAppend(&logger->writer);
			}
			else
			{
				err.u = _BLLogger_OpenCreate(&logger->writer);
			}
			if (err.u) break;
			logger->writer.logMode = logMode;
		}
	} while (false);
	return err;
}

void BLLogger_Delete(PBLLogger * ppLogger)
{
	if (ppLogger && *ppLogger)
	{
		PBLLogger logger = *ppLogger;
		if (logger->writer.file.hFile != NULL && logger->writer.file.hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(logger->writer.file.hFile);
			logger->writer.file.hFile = INVALID_HANDLE_VALUE;
		}
		BLArray_Delete(&logger->writer.filePath);
		free((void*)logger);
		*ppLogger = NULL;
	}
}

BLError BLLogger_Put(PBLLogger pLogger, uint16_t src_id, uint16_t src_line, BLLogType t, void * pvData)
{
	BLError err = BLError_MakeWin(ERROR_SUCCESS);
	do {
		if (pLogger->wrptr == pLogger->end)
		{
			err = BLLogger_Flush(pLogger);
			if (err.u) break;
		}

	} while (false);
	return err;
}
