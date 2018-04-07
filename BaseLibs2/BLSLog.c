#include "stdafx.h"
#include "BLTypes.h"
#include "BLError.h"
#include "BLArray.h"
#include "BLString.h"
#define	_BLSLog_c
#include "BLSLog.h"

BLSLog gLogger = { 0 };

const wchar_t* BLSLog_LogLevelLabels[] = {
	L"DEBUG",
	L"INFO",
	L"ERROR"
};

BLError BLSLog_Open(const wchar_t * logFilePath, BLSLogLevel ll)
{
	static const wchar_t BOM = 0xfeff;
	BLError err = BLError_MakeErrno(0);
	do {
		err.typedNumber.err = _wfopen_s(&gLogger.pf, logFilePath, L"r,ccs=UTF-16LE");
		if (gLogger.pf == NULL)
		{ // a new file is opened.
			err.typedNumber.err = _wfopen_s(&gLogger.pf, logFilePath, L"w,ccs=UTF-16LE");
			if (err.typedNumber.err) break;
			fwprintf(gLogger.pf, L"%wc", BOM);
		}
		else
		{ // an existing file is opened for appending.
			fclose(gLogger.pf); gLogger.pf = NULL;
			err.typedNumber.err = _wfopen_s(&gLogger.pf, logFilePath, L"a,ccs=UTF-16LE");
		}
		BLArray_Delete(&gLogger.filePath);
		gLogger.filePath = BLString_NewW(logFilePath, 0);
		InitializeCriticalSection(&gLogger.cs);
		gLogger.ll = ll;
	} while (false);
	return err;
}

BLError BLSLog_Close()
{
	BLError err = BLError_MakeWin(ERROR_SUCCESS);
	do {
		DeleteCriticalSection(&gLogger.cs);
		BLArray_Delete(&gLogger.filePath);
		err.typedNumber.err = fclose(gLogger.pf);
		gLogger.pf = NULL;
	} while (false);
	return err;
}
