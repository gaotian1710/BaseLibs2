#include "stdafx.h"
#define _BLARRAY_C
#include "BLArray.h"

size_t BLUnitSizes[] = {
	sizeof(char),
	sizeof(wchar_t),
	sizeof(int8_t),
	sizeof(int16_t),
	sizeof(int32_t),
	sizeof(int64_t),
	sizeof(uint8_t),
	sizeof(uint16_t),
	sizeof(uint32_t),
	sizeof(uint64_t),
	sizeof(float),
	sizeof(double),
	sizeof(_Fcomplex),
	sizeof(_Dcomplex),
	sizeof(int8_t*)
};

void BLArray_Init(PBLArray p, size_t cbPureData)
{
	p->end.c = p->data.c + cbPureData;
	memset(p->data.c, 0, cbPureData);
}
PBLArray BLArray_New(size_t cUnits, BLTypes t)
{
	size_t cbPureData = cUnits * BLUnitSizes[t];
	size_t cbAlloc = sizeof(BLArray) + cbPureData;
	PBLArray p = (PBLArray)malloc(cbAlloc);
	BLArray_Init(p, cbPureData);
	return p;
}

void BLArray_Delete(PBLArray *pp)
{
	if (pp && *pp)
	{
		free(*pp);
		*pp = NULL;
	}
}

size_t BLArray_ByteCount(PBLArray p)
{
	return (p->end.c - p->data.c);
}

size_t BLArray_UnitCount(PBLArray p, BLTypes t)
{
	return BLArray_ByteCount(p) / BLUnitSizes[t];
}

PBLBuffer BLBuffer_New(size_t cUnits, BLTypes t)
{
	size_t cbPureData = cUnits * BLUnitSizes[t];
	size_t cbAlloc = sizeof(BLBuffer) + cbPureData;
	PBLBuffer p = (PBLBuffer)malloc(cbAlloc);
	p->getter.c = p->arrayData.data.c;
	p->putter.c = p->arrayData.data.c;
	BLArray_Init(&(p->arrayData), cbPureData);
	return p;
}

void BLBuffer_Delete(PBLBuffer * pp)
{
	if (pp && *pp)
	{
		free(*pp);
		*pp = NULL;
	}
}

size_t BLBuffer_UnitCount(PBLBuffer p, BLTypes t)
{
	return BLArray_UnitCount(&(p->arrayData), t);
}

void BLBuffer_Clear(PBLBuffer p)
{
	memset(p->arrayData.data.c, 0, p->arrayData.end.c - p->arrayData.data.c);
	p->putter.c = p->arrayData.data.c;
	p->getter.c = p->arrayData.data.c;
}


#pragma region unit putter and unit getter
typedef void(*BLUnitPutter)(PBLBuffer p, const void* data);
typedef void(*BLUnitGetter)(PBLBuffer p, void* data);

#pragma endregion unit putter and unit getter
