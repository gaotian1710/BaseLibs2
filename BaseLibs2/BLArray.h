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
	BLType_ptr
} BLTypes;

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
} BLCPtr, *PBLCPtr;

typedef union {
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
} BLData, *PBLData;

typedef struct {
	wchar_t* pwc;
	size_t ccLen;
} BLWriteBuffer;

typedef struct {
	BLCPtr end;
	BLData data;
} BLArray, *PBLArray;

typedef struct {
	BLPtr putter;
	BLCPtr getter;
	BLArray arrayData;
} BLBuffer, *PBLBuffer;

#if defined(__cplusplus)
extern "C" {
#endif
	PBLArray BLArray_New(size_t cUnits, BLTypes t);

	void BLArray_Delete(PBLArray *pp);

	size_t BLArray_ByteCount(PBLArray p);

	size_t BLArray_UnitCount(PBLArray p, BLTypes t);

	PBLBuffer BLBuffer_New(size_t cUnits, BLTypes t);

	void BLBuffer_Delete(PBLBuffer *pp);

	size_t BLBuffer_UnitCount(PBLBuffer p, BLTypes t);

	PBLBuffer BLBuffer_ReadFileA(PBLArray utf8Filename);

	PBLBuffer BLBuffer_ReadFileW(PBLArray utf16Filename);

	void BLBuffer_Clear(PBLBuffer p);
#if defined(__cplusplus)
}
#endif

#if !defined(_BLARRAY_C)
#if defined(__cplusplus)
extern "C" size_t BLUnitSizes[];
#else
extern size_t BLUnitSizes[];
#endif
#endif
