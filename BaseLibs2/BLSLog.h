/*!
\description Simple logging library
*/
#pragma once

/*!
\description log devel enumeration
*/
typedef enum {
	BLSLogLevel_Debug,
	BLSLogLevel_Info,
	BLSLogLevel_Error
} BLSLogLevel;

/*!
\struct BLSLog
\description structure organizing a file logging channel
*/
typedef struct _BLSLog {
	CRITICAL_SECTION cs;
	SYSTEMTIME st;
	FILE* pf;
	BLSLogLevel ll; // log level
	PBLArray filePath; // wide character absolute path
} BLSLog, *PBLSLog;

#if defined(__cplusplus)
extern "C" {
#endif
	/*!
	\brief open a log file as a UTF-16LE text file in append mode if it exists or 
	newly creating mode if it does not exist.
	\param logFilePath [in] file path
	\param ll [in] log level
	\return error code is one of unix errno which _wfopen_s() returns.
	*/
	BLError BLSLog_Open(const wchar_t* logFilePath, BLSLogLevel ll);

	/*!
	\brief close a log file
	\return error code is one of unix errno which fclose() returns.
	*/
	BLError BLSLog_Close();

	// the following two extern global variables are not used by application codes but
	// only by macros at the bottom of this file.
#if !defined(_BLSLog_c)
	extern BLSLog gLogger;
	extern const wchar_t* BLSLog_LogLevelLabels[];
#endif
#if defined(__cplusplus)
}
#endif

#define BLSLog_Debug(...) { \
	EnterCriticalSection(&gLogger.cs); \
	if (gLogger.ll <= BLSLogLevel_Debug) {	\
		GetLocalTime(&gLogger.st); \
		fwprintf(gLogger.pf, L"%04d-%02d-%02d %02d:%02d:%02d.%03d,[%ws],", \
				gLogger.st.wYear, gLogger.st.wMonth, gLogger.st.wDay, \
				gLogger.st.wHour, gLogger.st.wMinute, gLogger.st.wSecond, gLogger.st.wMilliseconds, \
				BLSLog_LogLevelLabels[BLSLogLevel_Debug]); \
			fwprintf(gLogger.pf, __VA_ARGS__); \
			fwprintf(gLogger.pf, L"\n"); \
		} \
	LeaveCriticalSection(&gLogger.cs); \
}

#define BLSLog_Info(...) { \
	EnterCriticalSection(&gLogger.cs); \
	if (gLogger.ll <= BLSLogLevel_Info) {	\
	GetLocalTime(&gLogger.st); \
	fwprintf(gLogger.pf, L"%04d-%02d-%02d %02d:%02d:%02d.%03d,[%ws],", \
			gLogger.st.wYear, gLogger.st.wMonth, gLogger.st.wDay, \
			gLogger.st.wHour, gLogger.st.wMinute, gLogger.st.wSecond, gLogger.st.wMilliseconds, \
			BLSLog_LogLevelLabels[BLSLogLevel_Info]); \
		fwprintf(gLogger.pf, __VA_ARGS__); \
		fwprintf(gLogger.pf, L"\n"); \
	} \
	LeaveCriticalSection(&gLogger.cs); \
}


#define BLSLog_Error(...) { \
	EnterCriticalSection(&gLogger.cs); \
	if (gLogger.ll <= BLSLogLevel_Error) {	\
	GetLocalTime(&gLogger.st); \
	fwprintf(gLogger.pf, L"%04d-%02d-%02d %02d:%02d:%02d.%03d,[%ws],", \
			gLogger.st.wYear, gLogger.st.wMonth, gLogger.st.wDay, \
			gLogger.st.wHour, gLogger.st.wMinute, gLogger.st.wSecond, gLogger.st.wMilliseconds, \
			BLSLog_LogLevelLabels[BLSLogLevel_Error]); \
		fwprintf(gLogger.pf, __VA_ARGS__); \
		fwprintf(gLogger.pf, L"\n"); \
	} \
	LeaveCriticalSection(&gLogger.cs); \
}
