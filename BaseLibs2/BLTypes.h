#pragma once
typedef enum {
	BLType_c,
	BLType_wc,
	BLType_i8,
	BLType_i16,
	BLType_i32,
	BLType_i64,
	BLType_ui8,
	BLType_ui16,
	BLType_ui32,
	BLType_ui64,
	BLType_f,
	BLType_d,
	BLType_fc,
	BLType_dc,
	BLType_ptr,
	BLType_type,
	BLType_ccstr,
	BLType_cwcstr,
	BLType_cstr,
	BLType_wcstr
} BLTypes;


typedef union _BLData1 {
	char c[1];
	wchar_t wc[1];
	int8_t i8[1];
	int16_t i16[1];
	int32_t i32[1];
	int64_t i64[1];
	uint8_t ui8[1];
	uint16_t ui16[1];
	uint32_t ui32[1];
	uint64_t ui64[1];
	float f[1];
	double d[1];
	_Fcomplex fc[1];
	_Dcomplex dc[1];
	int8_t* ptr[1];
	BLTypes type[1];
	const char* ccstr[1];
	const wchar_t* cwcstr[1];
	char* cstdr[1];
	wchar_t* wcstr[1];
} BLData1, *PBLData1;

typedef const BLData1 *PCBLData1;

typedef union _BLData {
	char c[0];
	wchar_t wc[0];
	int8_t i8[0];
	int16_t i16[0];
	int32_t i32[0];
	int64_t i64[0];
	uint8_t ui8[0];
	uint16_t ui16[0];
	uint32_t ui32[0];
	uint64_t ui64[0];
	float f[0];
	double d[0];
	_Fcomplex fc[0];
	_Dcomplex dc[0];
	int8_t* ptr[0];
	BLTypes type[0];
	const char* ccstr[0];
	const wchar_t* cwcstr[0];
	char* cstdr[0];
	wchar_t* wcstr[0];
} BLData, *PBLData;

typedef union {
	char* c;
	wchar_t* wc;
	int8_t* i8;
	int16_t* i16;
	int32_t* i32;
	int64_t* i64;
	uint8_t* ui8;
	uint16_t* ui16;
	uint32_t* ui32;
	uint64_t* ui64;
	float* f;
	double* d;
	_Fcomplex* fc;
	_Dcomplex* dc;
	int8_t** ptr;
	BLTypes* type;
	const char* *ccstr;
	const wchar_t* *cwcstr;
	char* *cstr;
	wchar_t* *wcstr;
} BLPtr, *PBLPtr;

typedef union {
	const char* c;
	const wchar_t* wc;
	const int8_t* i8;
	const int16_t* i16;
	const int32_t* i32;
	const int64_t* i64;
	const uint8_t* ui8;
	const uint16_t* ui16;
	const uint32_t* ui32;
	const uint64_t* ui64;
	const float* f;
	const double* d;
	const _Fcomplex* fc;
	const _Dcomplex* dc;
	const int8_t** ptr;
	const BLTypes* type;
	const char* const *ccstr;
	const wchar_t* const *cwcstr;
	char* const *cstr;
	wchar_t* const *wcstr;
} BLCPtr, *PBLCPtr;

typedef float(*BLNorm)(BLCPtr p);
typedef void(*BLCopyS)(BLPtr dst, BLCPtr src);

#if !defined(_BLTypes_c)
#if defined(__cplusplus)
extern "C" const wchar_t* const BLTypeLabels[];
extern "C" const BLNorm BLNormFunctions[];
extern "C" const BLCopyS BLCopySFunctions[];
extern "C" const BLCopyS BLReciprocalSFunctions[];
#else
extern const wchar_t* const BLTypeLabels[];
extern const BLNorm BLNormFunctions[];
extern const BLCopyS BLCopySFunctions[];
extern const BLCopyS BLReciprocalSFunctions[];
#endif
#endif

#if defined(_CRTDBG_MAP_ALLOC)
#define DumpHeap	_CrtDumpMemoryLeaks
#else
#define DumpHeap
#endif
