#pragma once


typedef struct {
	wchar_t* pwc;
	size_t ccLen;
} BLWriteBuffer, *PBLWriteBuffer;

typedef const BLWriteBuffer *PCBLWriteBuffer;

typedef struct {
	BLCPtr end;
	BLData data;
} BLArray, *PBLArray;

typedef const BLArray *PCBLArray;

typedef struct {
	BLPtr putter;
	BLCPtr getter;
	BLArray arrayData;
} BLBuffer, *PBLBuffer;

typedef const BLBuffer *PCBLBuffer;

#if defined(__cplusplus)
extern "C" {
#endif
	PBLArray BLArray_Init(PBLArray p, size_t cbPureData);

	PBLBuffer BLBuffer_New(size_t cUnits, BLTypes t);

	void BLBuffer_Delete(PBLBuffer *pp);

	size_t BLBuffer_UnitCount(PCBLBuffer p, BLTypes t);

	/*!
	\brief read data from a file
	\param utf8Filename [in] filename given to win32 CreateFile() or std-c open()
	\param ppData [out] pointer pointer to the data array to fill with the data read from the file.
	\return error code can be std-c errno or win32 error code.
	*/
	BLError BLBuffer_ReadFileA(PCBLArray utf8Filename, PBLArray* ppData);

	/*!
	\brief read data from a file
	\param utf16Filename [in] filename given to win32 CreateFile() or std-c open()
	\param ppData [out] pointer pointer to the data array to fill with the data read from the file.
	\return error code can be std-c errno or win32 error code.
	*/
	BLError BLBuffer_ReadFileW(PCBLArray utf16Filename, PBLArray* ppData);

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

#define BLArray_New(cUnits, t) \
( \
	BLArray_Init((PBLArray)malloc(sizeof(BLPtr) + (cUnits) * BLUnitSizes[(t)]), (cUnits) * BLUnitSizes[(t)]) \
)

#define BLArray_NewAlloca(cUnits, t) \
( \
	BLArray_Init((PBLArray)alloca(sizeof(BLPtr) + (cUnits) * BLUnitSizes[(t)]), (cUnits) * BLUnitSizes[(t)]) \
)

#define BLArray_Delete(pp)	if ((pp) && *(pp)) { free(*(pp)); *(pp) = NULL; }

#define BLArray_ByteCount(p) (((PBLArray)(p))->end.c - ((PBLArray)(p))->data.c)

#define BLArray_UnitCount(p, t) ((BLArray_ByteCount(p)) / BLUnitSizes[(t)])