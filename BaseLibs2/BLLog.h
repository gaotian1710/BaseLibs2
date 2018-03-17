#pragma once
/*!
\file BLLog.h
*/

typedef enum {
	BLLogLevel_Fatal,
	BLLogLevel_Error,
	BLLogLevel_Info,
	BLLogLevel_Debug,
	BLLogLevel_Invalid,
} BLLogLevel;

typedef enum {
	BLLogWriteTrigger_Flush,
	BLLogWriteTrigger_BufferFull,
	BLLogWriteTrigger_Invalid,
} BLLogWriteTrigger;

typedef enum {
	BLLogIniSec_log
} BLLogIniSec;

typedef enum {
	BLLogIniItem_path,
	BLLogIniItem_level,
	BLLogIniItem_trigger,
	BLLogIniItem_bufsize,
	BLLogIniItem_filesize,
	BLLogIniItem_rolling,
} BLLogIniItem;

#define BLLOG_ROLLING_MAX	4

typedef struct _BLLogIni {
	BLLogLevel ll;
	BLLogWriteTrigger lwt;
	size_t cFiles;
	size_t cbFile;
	size_t cbBuf;
	PBLArray filePath;
} BLLogIni, *PBLLogIni;

typedef const BLLogIni *PCBLLogIni;

typedef struct _BLLog {
	// my own data
	CRITICAL_SECTION cs;
	DWORD processId;
	PBLArray moduleName; // module base name and extension (*.exe, *.dll, etc.)

	// depending on .ini file
	PBLLogIni ini;
	size_t iBuf; // buffer index (iBuf = 0..1)
	PBLBuffer buf[2];
} BLLog, *PBLLog;


#if defined(__cplusplus)
extern "C" {
#endif
	/*!
	\brief read ini file
	\param pp [out] null pointer or any allocated pointer. Heap memory block is always 
		allocated in every call.
	\param iniFilePath [in] ini file absolute path
	\return win32 error code
	*/
	DWORD BLLogIni_Read(PBLLogIni *pp, const wchar_t* iniFilePath);

	/*!
	\brief free the memory block allocated to *pp
	\param pp [in] pointer pointer to BLLogIni object.
	*/
	void BLLogIni_Delete(PBLLogIni* pp);

	/*!
	\brief duplicate an object.
	\param p [in] 
	*/
	PBLLogIni BLLogIni_Dup(PCBLLogIni p);

	/*!
	\brief create a new logger object
	\param pp [out] pointer pointer to the newly created logger object
	\param ini [in] initialization parameter
	\param modNameCandidates [in] module name candidates
	\return win32 error code
	*/
	DWORD BLLog_New(PBLLog *pp, PCBLLogIni ini, const wchar_t* *modNameCandidates);

	/*!
	\brief release resources used by the logger object.
	\param pp [in,out] pointer pointer to logger object to release.
	*/
	void BLLog_Delete(PBLLog *pp);

	/*!
	\brief get the write buffer in order to append new string to the currently selected
		BLLog internal buffer.
	\param p [in] BLLog object
	\param wb [out] write buffer
	\return error code
	*/
	DWORD BLLog_Get(PBLLog p, PBLWriteBuffer wb);

	/*!
	\brief get another write buffer. It is used when the previously gotten buffer is too
		small. BLLog_GetAnother() flush the currently selected internal buffer if the flush
		trigger is BLLogWriteTrigger_BufferFull.
	\param p [in,out] BLLog object
	\param wb [in,out] exported write buffer
	\return error code gotten in writing log buffer to log file.
	*/
	DWORD BLLog_GetAnother(PBLLog p, PBLWriteBuffer wb);

	/*
	\brief discard the write buffer and 
	*/
	void BLLog_Cancel(PBLLog p);

	DWORD BLLog_Release(PBLLog p, BLWriteBuffer writeBuffer);

	DWORD BLLog_Flush(PBLLog p);
#if defined(__cplusplus)
}
#endif

#define BLLOG_DATETIME_FORMAT_DESCRIPTOR	L"%04d-%02d-%02dT%02d:%02d:%02d.%03dZ,"
#define BLLOG_DATETIME_TEMPLATE				L"YYYY-MM-DDThh:mm:ss.sssZ,"
#define BLLOG_DATETIME_LENGTH				wcslen(BLLOG_DATETIME_TEMPLATE)
#define BLLOG_LOGLEVEL_FORMAT_DESCRIPTOR	L"%1d,"
#define BLLOG_LOGLEVEL_TEMPLATE				L"9,"
#define BLLOG_LOGLEVEL_LENGTH				wcslen(BLLOG_LOGLEVEL_TEMPLATE)
#define BLLOG_MODULENAME_FORMAT_DESCRIPTOR	L"%ws,"
#define BLLOG_MODULENAME_LENGTHESTIMATE		33
#define BLLOG_PROCESSID_FORMAT_DESCRIPTOR	L"%04d,"
#define BLLOG_PROCESSID_TEMPLATE			L"9999,"
#define BLLOG_PROCESSID_LENGTH				wcslen(BLLOG_PROCESSID_TEMPLATE)
#define BLLOG_CODETYPE_FORMAT_DESCRIPTOR	L"%1d,"
#define BLLOG_CODETYPE_TEMPLATE				L"9,"
#define BLLOG_CODETYPE_LENGTH				wcslen(BLLOG_CODETYPE_TEMPLATE)
#define BLLOG_CODE_FORMAT_DESCRIPTOR		L"0x%08x"
#define BLLOG_CODE_TEMPLATE					L"0xffffffff,"
#define BLLOG_CODE_LENGTH					wcslen(BLLOG_CODE_TEMPLATE)
#define BLLOG_SOURCEFILE_FORMAT_DESCRIPTOR	L"%hs,"
#define BLLOG_SOURCEFILE_LENGTHESTIMATE		33
#define BLLOG_SOURCELINE_FORMAT_DESCRIPTOR	L"%d,"
#define BLLOG_SOURCELINE_TEMPLATE			L"9999,"
#define BLLOG_SOURCELINE_LENGTH				wcslen(BLLOG_SOURCELINE_TEMPLATE)
#define BLLOG_HEADER_FORMAT_DESCRIPTOR	\
	BLLOG_DATETIME_FORMAT_DESCRIPTOR \
	BLLOG_LOGLEVEL_FORMAT_DESCRIPTOR \
	BLLOG_MODULENAME_FORMAT_DESCRIPTOR \
	BLLOG_PROCESSID_FORMAT_DESCRIPTOR
#define BLLOG_HEADER_LENGTH(modname)	\
	(BLLOG_DATETIME_LENGTH + BLLOG_LOGLEVEL_LENGTH + wcslen(modname) + BLLOG_PROCESSID_LENGTH)
