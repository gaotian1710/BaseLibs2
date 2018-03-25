#pragma once

typedef int(*BLTupleElementFormatter)(PBLBuffer buffer, PCBLData1 data);

typedef struct _BLTable {
	const wchar_t* *headline;
	const BLTupleElementFormatter *formatters;
	const BLTypes *types;
	PBLBuffer buffer;
} BLTable, *PBLTable;

typedef const BLTable *PCBLTable;

#if defined(__cplusplus)
extern "C" {
#endif
	PBLArray BLTuple_New(PCBLTable table);

	void BLTuple_Delete(PBLArray *ppTuple);

	BLError BLTuple_ToWStr(PBLTable table, PCBLArray tuple);

	BLError BLTuple_FromWStr(PBLTable table, PBLArray tuple);
#if defined(__cplusplus)
}
#endif
