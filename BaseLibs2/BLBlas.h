#pragma once
typedef struct _BLRange {
	BLPtr scan;
	const BLCPtr end;
} BLRange, *PBLRange;

typedef struct _BLCRange {
	BLCPtr scan;
	const BLCPtr end;
} BLCRange, *PBLCRange;

#define BLRange_Init(ptrScan, ptrEnd) { \
	{ (char*)(ptrScan) }, { (const char* const)(ptrEnd) } \
}

#define BLCRange_Init(ptrScan, ptrEnd) { \
	{ (const char*)(ptrScan) }, { (const char* const)(ptrEnd) } \
}


#if defined(__cplusplus)
extern "C" {
#endif
	inline int BLRange_Check1C(PBLCRange range, BLTypes t)
	{
		int diffBytes = (int)(range->end.c - range->scan.c);
		int diffFraction = diffBytes % BLUnitSizes[t];
		return (diffBytes > 0 && diffFraction == 0) ? 0 : ERANGE;
	}

	inline int BLRange_Check1(PBLRange range, BLTypes t)
	{
		int diffBytes = (int)(range->end.c - range->scan.c);
		int diffFraction = diffBytes % BLUnitSizes[t];
		return (diffBytes > 0 && diffFraction == 0) ? 0 : ERANGE;
	}

	inline int BLRange_Check2(PBLRange range0, PBLCRange range1, BLTypes t)
	{
		int i0 = BLRange_Check1(range0, t);
		int diffBytes0 = (int)(range0->end.c - range0->scan.c);
		int diffBytes1 = (int)(range1->end.c - range1->scan.c);
		int i1 = (diffBytes0 == diffBytes1) ? 0 : ERANGE;
		return i0 || i1 ? ERANGE : 0;
	}

	inline int BLRange_Check2V(PBLRange range0, PBLRange range1, BLTypes t)
	{
		int i0 = BLRange_Check1(range0, t);
		int diffBytes0 = (int)(range0->end.c - range0->scan.c);
		int diffBytes1 = (int)(range1->end.c - range1->scan.c);
		int i1 = (diffBytes0 == diffBytes1) ? 0 : ERANGE;
		return i0 || i1 ? ERANGE : 0;
	}

	inline int BLRange_Check3(PBLRange range0, PBLCRange range1, PBLCRange range2, BLTypes t)
	{
		int i0 = BLRange_Check2(range0, range1, t);
		int i1 = BLRange_Check2(range0, range2, t);
		return i0 || i1 ? ERANGE : 0;
	}

#if defined(_DEBUG)
#define BLRange_Check1DBG(range,t) { \
	int ierr = BLRange_Check1(range,t); \
	if (ierr) return ierr; \
}

#define BLRange_Check1CDBG(range,t) { \
	int ierr = BLRange_Check1C(range,t); \
	if (ierr) return ierr; \
}

#define BLRange_Check2DBG(range0, range1, t) { \
	int ierr = BLRange_Check2(range0, range1, t); \
	if (ierr) return ierr; \
}

#define BLRange_Check2VDBG(range0, range1, t) { \
	int ierr = BLRange_Check2V(range0, range1, t); \
	if (ierr) return ierr; \
}

#define BLRange_Check3DBG(range0, range1, range2, t) { \
	int ierr = BLRange_Check3(range0, range1, range2, t); \
	if (ierr) return ierr; \
}

#else
#define BLRange_Check1DBG(range,t)
#define BLRange_Check1CDBG(range,t)
#define BLRange_Check2DBG(range0, range1, t)
#define BLRange_Check3DBG(range0, range1, range2, t)
#endif

#pragma region float operations
#pragma region _1v0c operations
	int BLBlas_ZEqZeroF(BLRange z);
	int BLBlas_ZEqOneF(BLRange z);
	int BLBlas_ZEqMinusOneF(BLRange z);
#pragma endregion _1v0c operations
#pragma region _1v1c operations
	int BLBlas_ZEqXF(BLRange z, BLCRange x);
	int BLBlas_ZAddEqXF(BLRange z, BLCRange x);
	int BLBlas_ZSubEqXF(BLRange z, BLCRange x);
	int BLBlas_ZMulEqXF(BLRange z, BLCRange x);
	int BLBlas_ZDivEqXF(BLRange z, BLCRange x);
	int BLBlas_ZEqNegateXF(BLRange z, BLCRange x);
	int BLBlas_ZEqReciprocalXF(BLRange z, BLCRange x);
#pragma endregion _1v0c operations
#pragma region _2v operations
	int BLBlas_Swap(BLRange x, BLRange y);
#pragma endregion _2v operations
#pragma region _1v2c operations
	int BLBlas_ZEqXAddYF(BLRange z, BLCRange x, BLCRange y);
	int BLBlas_ZEqXSubYF(BLRange z, BLCRange x, BLCRange y);
	int BLBlas_ZEqXMulYF(BLRange z, BLCRange x, BLCRange y);
	int BLBlas_ZEqXDivYF(BLRange z, BLCRange x, BLCRange y);
#pragma endregion _1v2c operations
#pragma endregion float operations

#if defined(__cplusplus)
}
#endif
