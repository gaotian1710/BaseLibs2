#pragma once
/*!
\file BLLog.h
*/

typedef enum {
	BLLogMode_AFO, // auto flush and open only flushing
	BLLogMode_AFCO, // continuously opened
	BLLogMode_EFO // each time flush and open
} BLLogMode;

typedef enum {
	BLLogType_c = BLType_c,
	BLLogType_wc = BLType_wc,
	BLLogType_i8 = BLType_i8,
	BLLogType_i16 = BLType_i16,
	BLLogType_i32 = BLType_i32,
	BLLogType_i64 = BLType_i64,
	BLLogType_ui8 = BLType_ui8,
	BLLogType_ui16 = BLType_ui16,
	BLLogType_ui32 = BLType_ui32,
	BLLogType_ui64 = BLType_ui64,
	BLLogType_f = BLType_f,
	BLLogType_d = BLType_d,
	BLLogType_fc = BLType_fc,
	BLLogType_dc = BLType_dc,
	BLLogType_ptr = BLType_ptr,
	BLLogType_Array_c,
	BLLogType_Array_wc,
	BLLogType_Array_i8,
	BLLogType_Array_i16,
	BLLogType_Array_i32,
	BLLogType_Array_i64,
	BLLogType_Array_ui8,
	BLLogType_Array_ui16,
	BLLogType_Array_ui32,
	BLLogType_Array_ui64,
	BLLogType_Array_f,
	BLLogType_Array_d,
	BLLogType_Array_fc,
	BLLogType_Array_dc,
	BLLogType_Array_ptr
} BLLogType, *PBLLogType;

typedef struct {
	struct timespec time;
	DWORD
		pid,
		tid;
	uint16_t
		proj_id,
		src_id,
		src_line;
	BLTypes type;
	BLError err;
} BLLogHeader, *PBLLogHeader;

typedef struct {
	BLLogHeader header;
	BLData1 data;
} BLLogData, *PBLLogData;

typedef const BLLogData *PCBLLogData;

typedef struct {
	PBLArray filePath;
	union {
		HANDLE hFile; // win32 file handle
		int iFD; // std-c file descriptor
	} file;
	BLLogMode logMode;
} BLLogWriter, *PBLLogWriter;

typedef struct {
	BLLogHeader header; // header template
	BLLogWriter writer;
	PCBLLogData end;
	PBLLogData wrptr;
	BLLogData record[0];
} BLLogger, *PBLLogger;

#if defined(__cplusplus)
extern "C" {
#endif
	BLError BLLogger_New(
		const wchar_t *filePath,
		size_t cRecord,
		BLLogMode logMode,
		const wchar_t* proj_name,
		PBLLogger* ppLogger);

	void BLLogger_Delete(PBLLogger* ppLogger);

	BLError BLLogger_Put(
		PBLLogger pLogger,
		uint16_t src_id,
		uint16_t src_line,
		BLLogType t,
		void* pvData);

	BLError BLLogger_PutMT(
		PBLLogger pLogger,
		DWORD tid,
		uint16_t src_id,
		uint16_t src_line,
		BLLogType t,
		void* pvData);


	BLError BLLogger_Flush(PBLLogger pLogger);
#if defined(__cplusplus)
}
#endif
