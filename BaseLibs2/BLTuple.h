#pragma once

typedef struct {
	BLData1 data;
	BLTypes type;
} BLVariant, *PBLVariant;

typedef const BLVariant *PCBLVariant;

typedef struct {
	PCBLVariant end;
	BLVariant tuple[0];
} BLTuple, *PBLTuple;

typedef const BLTuple *PCBLTuple;

typedef enum {
	BLTupleColumnPosition_OnlyOne,
	BLTupleColumnPosition_Begin,
	BLTupleColumnPosition_Other,
	BLTupleColumnPosition_End
} BLTupleColumnPosition;

typedef int (*BLTupleFormatter)(
	BLTupleColumnPosition pos,
	wchar_t* buffer,
	size_t bufferLength, 
	const BLData1* data);

#if defined(__cplusplus)
extern "C" {
#endif
	PBLTuple BLTuple_New(size_t cElements);

	void BLTuple_Delete(PBLTuple* pp);

	size_t BLTuple_Count(PCBLTuple p);

	int BLTuple_Format(PBLArray *ppBuffer, PCBLTuple tuple);
#if defined(__cplusplus)
}
#endif
