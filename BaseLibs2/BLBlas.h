#pragma once
typedef struct _BLRange {
	BLPtr scan;
	const BLCPtr end;
} BLRange, *PBLRange;

typedef struct _BLCRange {
	BLCPtr scan;
	const BLCPtr end;
} BLCRange, *PBLCRange;

typedef void (*BLBlas_ScalarSubstitution)(BLPtr dst, BLCPtr src);
typedef int (*BLBlas_ScalarFromTwoVectors)(BLPtr dst, BLCRange x, BLCRange y);


typedef int(*BLBlas_1v0c)(BLRange);
typedef int(*BLBlas_1v1c)(BLRange, BLCRange);
typedef int(*BLBlas_1v1cs)(BLRange, BLCPtr);
typedef int(*BLBlas_2v)(BLRange, BLRange);
typedef int(*BLBlas_1v2c)(BLRange, BLCRange, BLCRange);
typedef int(*BLBlas_1vs2c)(BLPtr, BLCRange, BLCRange);
typedef int(*BLBlas_1v1c1cs)(BLRange, BLCRange, BLCPtr);
typedef void(*BLBlas_1vs1cs)(BLPtr, BLCPtr);
typedef void(*BLBlas_1vs0c)(BLPtr);
typedef float(*BLBlas_norm)(BLCPtr);

typedef struct {
	BLBlas_1v0c fillOnes;
	BLBlas_1v0c fillZeros;
	BLBlas_1v0c fillMinusOnes;
	BLBlas_1v1c zEqX;
	BLBlas_1v1c zAddEqX;
	BLBlas_1v1c zSubEqX;
	BLBlas_1v1c zMulEqX;
	BLBlas_1v1c zDivEqX;
	BLBlas_1v1c zEqNegateX;
	BLBlas_1v1c zEqReciprocalX;
	BLBlas_1v1cs zMulEqXs;
	BLBlas_2v swap;
	BLBlas_1v2c zEqXAddY;
	BLBlas_1v2c zEqXSubY;
	BLBlas_1v2c zEqXMulY;
	BLBlas_1v2c zEqXDivY;
	BLBlas_1v1c1cs zAddEqXMulYs;
	BLBlas_1vs2c zEqXInnerProductY;
	BLBlas_1vs1cs zsEqXs;
	BLBlas_1vs1cs zsEqConjXs;
	BLBlas_1vs1cs zsEqNegateXs;
	BLBlas_1vs1cs zsEqReciprocalXs;
	BLBlas_1vs0c zsEqZero;
	BLBlas_1vs0c zsEqOne;
	BLBlas_norm norm;
	BLTypes	t;
} BLBlasInterface, *PBLBlasInterface;

typedef const BLBlasInterface *PCBLBlasInterface;

#define BLRange_Init(ptrScan, ptrEnd) { \
	{ (char*)(ptrScan) }, { (const char* const)(ptrEnd) } \
}

#define BLCRange_Init(ptrScan, ptrEnd) { \
	{ (const char*)(ptrScan) }, { (const char* const)(ptrEnd) } \
}


#if defined(__cplusplus)
extern "C" {
#endif
#pragma region ranch check methods
#pragma region ranch check inline methods
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
		return (i0 || i1) ? ERANGE : 0;
	}

	inline int BLRange_Check2C(PBLCRange range0, PBLCRange range1, BLTypes t)
	{
		int i0 = BLRange_Check1C(range0, t);
		int diffBytes0 = (int)(range0->end.c - range0->scan.c);
		int diffBytes1 = (int)(range1->end.c - range1->scan.c);
		int i1 = (diffBytes0 == diffBytes1) ? 0 : ERANGE;
		return (i0 || i1) ? ERANGE : 0;
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
#pragma endregion ranch check inline methods

#define BLBlas_Return(file,line) return 0

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

#define BLRange_Check2CDBG(range0, range1, t) { \
	int ierr = BLRange_Check2C(range0, range1, t); \
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

#if defined(_CRTDBG_MAP_ALLOC)
#define BLBlas_Return(file,line) { \
	int ierr = _CrtCheckMemory() ? 0 : ERANGE; \
	if (ierr) wprintf(L"Heap corruption: %hs, %d\n", file, line); \
	return (ierr); \
}
#endif
#else
#define BLRange_Check1DBG(range,t)
#define BLRange_Check1CDBG(range,t)
#define BLRange_Check2DBG(range0, range1, t)
#define BLRange_Check3DBG(range0, range1, range2, t)
#endif
#pragma endregion ranch check methods


#pragma region float operations
#pragma region _1v0c float operations
	int BLBlas_ZEqZeroF(BLRange z);			/*!< z = 0; */
	int BLBlas_ZEqOneF(BLRange z);			/*!< z = 1; */
	int BLBlas_ZEqMinusOneF(BLRange z);		/*!< z = -1; */
#pragma endregion _1v0c float operations
#pragma region _1v1c float operations
	int BLBlas_ZEqXF(BLRange z, BLCRange x);	/*!< z = x; */
	int BLBlas_ZAddEqXF(BLRange z, BLCRange x);	/*!< z += x; */
	int BLBlas_ZSubEqXF(BLRange z, BLCRange x);	/*!< z -= x; */
	int BLBlas_ZMulEqXF(BLRange z, BLCRange x);	/*!< z *= x; */
	int BLBlas_ZDivEqXF(BLRange z, BLCRange x);	/*!< z /= x; */
	int BLBlas_ZEqNegateXF(BLRange z, BLCRange x);	/*!< z = -x; */
	int BLBlas_ZEqReciprocalXF(BLRange z, BLCRange x);	/*!< z = 1.0/x; */
	int BLBlas_ZMulEqXsF(BLRange z, BLCPtr x); /*!< z *= xs; */
#pragma endregion _1v0c float operations
#pragma region _2v float operations
	int BLBlas_SwapF(BLRange x, BLRange y);		/*!< swap(x, y); */
#pragma endregion _2v float operations
#pragma region _1v2c float operations
	int BLBlas_ZEqXAddYF(BLRange z, BLCRange x, BLCRange y);	/*!< z = x + y; */
	int BLBlas_ZEqXSubYF(BLRange z, BLCRange x, BLCRange y);	/*!< z = x - y; */
	int BLBlas_ZEqXMulYF(BLRange z, BLCRange x, BLCRange y);	/*!< z = x * y; */
	int BLBlas_ZEqXDivYF(BLRange z, BLCRange x, BLCRange y);	/*!< z = x / y; */
	int BLBlas_ZAddEqXMulYsF(BLRange z, BLCRange x, BLCPtr ys);	/*!< z += x * ys; ys is scalar. */
	int BLBlas_ZEqXInnerProductYF(BLPtr z, BLCRange x, BLCRange y);
#pragma endregion _1v2c float operations
	void BLBlas_ZsEqXsF(BLPtr zs, BLCPtr xs); /*!< zs = xs; scalar operation */
	void BLBlas_ZsEqNegateXsF(BLPtr zs, BLCPtr xs); /*!< zs = -xs */
	void BLBlas_ZsEqReciprocalXsF(BLPtr zs, BLCPtr xs); /*!< zs = 1.0/xs; scalar operation */
	void BLBlas_ZsEqZeroF(BLPtr zs); /*!< zs = 0 */
	void BLBlas_ZsEqOneF(BLPtr zs); /*!< zs = 1 */
	float BLBlas_NormF(BLCPtr xs); /*!< return norm(xs) */
#pragma endregion float operations

#pragma region double operations
#pragma region _1v0c double operations
	int BLBlas_ZEqZeroD(BLRange z);			/*!< z = 0; */
	int BLBlas_ZEqOneD(BLRange z);			/*!< z = 1; */
	int BLBlas_ZEqMinusOneD(BLRange z);		/*!< z = -1; */
#pragma endregion _1v0c double operations
#pragma region _1v1c double operations
	int BLBlas_ZEqXD(BLRange z, BLCRange x);	/*!< z = x; */
	int BLBlas_ZAddEqXD(BLRange z, BLCRange x);	/*!< z += x; */
	int BLBlas_ZSubEqXD(BLRange z, BLCRange x);	/*!< z -= x; */
	int BLBlas_ZMulEqXD(BLRange z, BLCRange x);	/*!< z *= x; */
	int BLBlas_ZDivEqXD(BLRange z, BLCRange x);	/*!< z /= x; */
	int BLBlas_ZEqNegateXD(BLRange z, BLCRange x);	/*!< z = -x; */
	int BLBlas_ZEqReciprocalXD(BLRange z, BLCRange x);	/*!< z = 1.0/x; */
	int BLBlas_ZMulEqXsD(BLRange z, BLCPtr x); /*!< z *= xs; */
#pragma endregion _1v0c double operations
#pragma region _2v double operations
	int BLBlas_SwapD(BLRange x, BLRange y);		/*!< swap(x, y); */
#pragma endregion _2v double operations
#pragma region _1v2c double operations
	int BLBlas_ZEqXAddYD(BLRange z, BLCRange x, BLCRange y);	/*!< z = x + y; */
	int BLBlas_ZEqXSubYD(BLRange z, BLCRange x, BLCRange y);	/*!< z = x - y; */
	int BLBlas_ZEqXMulYD(BLRange z, BLCRange x, BLCRange y);	/*!< z = x * y; */
	int BLBlas_ZEqXDivYD(BLRange z, BLCRange x, BLCRange y);	/*!< z = x / y; */
	int BLBlas_ZAddEqXMulYsD(BLRange z, BLCRange x, BLCPtr ys);	/*!< z += x * ys; ys is scalar. */
	int BLBlas_ZEqXInnerProductYD(BLPtr z, BLCRange x, BLCRange y);
#pragma endregion _1v2c double operations
	void BLBlas_ZsEqXsD(BLPtr zs, BLCPtr xs); /*!< zs = xs; scalar operation */
	void BLBlas_ZsEqNegateXsD(BLPtr zs, BLCPtr xs); /*!< zs = -xs */
	void BLBlas_ZsEqReciprocalXsD(BLPtr zs, BLCPtr xs); /*!< zs = 1.0/xs; scalar operation */
	void BLBlas_ZsEqZeroD(BLPtr zs); /*!< zs = 0 */
	void BLBlas_ZsEqOneD(BLPtr zs); /*! zs = 1 */
	float BLBlas_NormD(BLCPtr xs); /*!< return norm(xs) */
#pragma endregion double operations


	inline _Fcomplex _FCaddcc(_Fcomplex x, _Fcomplex y)
	{
		return _FCOMPLEX_(x._Val[0] + y._Val[0], x._Val[1] + y._Val[1]);
	}

	inline _Fcomplex _FCsubcc(_Fcomplex x, _Fcomplex y)
	{
		return _FCOMPLEX_(x._Val[0] - y._Val[0], x._Val[1] - y._Val[1]);
	}

#pragma region float complex operations
#pragma region _1v0c float complex operations
	int BLBlas_ZEqZeroFc(BLRange z);			/*!< z = 0; */
	int BLBlas_ZEqOneFc(BLRange z);			/*!< z = 1; */
	int BLBlas_ZEqMinusOneFc(BLRange z);		/*!< z = -1; */
#pragma endregion _1v0c float complex operations
#pragma region _1v1c float complex operations
	int BLBlas_ZEqXFc(BLRange z, BLCRange x);	/*!< z = x; */
	int BLBlas_ZAddEqXFc(BLRange z, BLCRange x);	/*!< z += x; */
	int BLBlas_ZSubEqXFc(BLRange z, BLCRange x);	/*!< z -= x; */
	int BLBlas_ZMulEqXFc(BLRange z, BLCRange x);	/*!< z *= x; */
	int BLBlas_ZDivEqXFc(BLRange z, BLCRange x);	/*!< z /= x; */
	int BLBlas_ZEqNegateXFc(BLRange z, BLCRange x);	/*!< z = -x; */
	int BLBlas_ZEqReciprocalXFc(BLRange z, BLCRange x);	/*!< z = 1.0/x; */
	int BLBlas_ZMulEqXsFc(BLRange z, BLCPtr x); /*!< z *= xs; */
#pragma endregion _1v0c float complex operations
#pragma region _2v float complex operations
	int BLBlas_SwapFc(BLRange x, BLRange y);		/*!< swap(x, y); */
#pragma endregion _2v float complex operations
#pragma region _1v2c float complex operations
	int BLBlas_ZEqXAddYFc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x + y; */
	int BLBlas_ZEqXSubYFc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x - y; */
	int BLBlas_ZEqXMulYFc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x * y; */
	int BLBlas_ZEqXDivYFc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x / y; */
	int BLBlas_ZAddEqXMulYsFc(BLRange z, BLCRange x, BLCPtr ys);	/*!< z += x * ys; ys is scalar. */
	int BLBlas_ZEqXInnerProductYFc(BLPtr z, BLCRange x, BLCRange y);
#pragma endregion _1v2c float complex operations
	void BLBlas_ZsEqXsFc(BLPtr zs, BLCPtr xs); /*!< zs = xs; scalar operation */
	void BLBlas_ZsEqConjXsFc(BLPtr zs, BLCPtr xs);
	void BLBlas_ZsEqNegateXsFc(BLPtr zs, BLCPtr xs); /*!< zs = -xs */
	void BLBlas_ZsEqReciprocalXsFc(BLPtr zs, BLCPtr xs); /*!< zs = 1.0/xs; scalar operation */
	void BLBlas_ZsEqZeroFc(BLPtr zs); /*!< zs = 0 */
	void BLBlas_ZsEqOneFc(BLPtr zs); /*! zs = 1 */
	float BLBlas_NormFc(BLCPtr xs); /*!< return norm(xs) */
#pragma endregion float complex operations


	inline _Dcomplex _Caddcc(_Dcomplex x, _Dcomplex y)
	{
		return _DCOMPLEX_(x._Val[0] + y._Val[0], x._Val[1] + y._Val[1]);
	}

	inline _Dcomplex _Csubcc(_Dcomplex x, _Dcomplex y)
	{
		return _DCOMPLEX_(x._Val[0] - y._Val[0], x._Val[1] - y._Val[1]);
	}

#pragma region double complex operations
#pragma region _1v0c double complex operations
	int BLBlas_ZEqZeroDc(BLRange z);			/*!< z = 0; */
	int BLBlas_ZEqOneDc(BLRange z);			/*!< z = 1; */
	int BLBlas_ZEqMinusOneDc(BLRange z);		/*!< z = -1; */
#pragma endregion _1v0c double complex operations
#pragma region _1v1c double complex operations
	int BLBlas_ZEqXDc(BLRange z, BLCRange x);	/*!< z = x; */
	int BLBlas_ZAddEqXDc(BLRange z, BLCRange x);	/*!< z += x; */
	int BLBlas_ZSubEqXDc(BLRange z, BLCRange x);	/*!< z -= x; */
	int BLBlas_ZMulEqXDc(BLRange z, BLCRange x);	/*!< z *= x; */
	int BLBlas_ZDivEqXDc(BLRange z, BLCRange x);	/*!< z /= x; */
	int BLBlas_ZEqNegateXDc(BLRange z, BLCRange x);	/*!< z = -x; */
	int BLBlas_ZEqReciprocalXDc(BLRange z, BLCRange x);	/*!< z = 1.0/x; */
	int BLBlas_ZMulEqXsDc(BLRange z, BLCPtr x); /*!< z *= xs; */
#pragma endregion _1v0c double complex operations
#pragma region _2v double complex operations
	int BLBlas_SwapDc(BLRange x, BLRange y);		/*!< swap(x, y); */
#pragma endregion _2v double complex operations
#pragma region _1v2c double complex operations
	int BLBlas_ZEqXAddYDc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x + y; */
	int BLBlas_ZEqXSubYDc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x - y; */
	int BLBlas_ZEqXMulYDc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x * y; */
	int BLBlas_ZEqXDivYDc(BLRange z, BLCRange x, BLCRange y);	/*!< z = x / y; */
	int BLBlas_ZAddEqXMulYsDc(BLRange z, BLCRange x, BLCPtr ys);	/*!< z += x * ys; ys is scalar. */
	int BLBlas_ZEqXInnerProductYDc(BLPtr z, BLCRange x, BLCRange y);
#pragma endregion _1v2c double complex operations
	void BLBlas_ZsEqXsDc(BLPtr zs, BLCPtr xs); /*!< zs = xs; scalar operation */
	void BLBlas_ZsEqConjXsDc(BLPtr zs, BLCPtr xs); /*! zs = conj(xs); scalar operation */
	void BLBlas_ZsEqNegateXsDc(BLPtr zs, BLCPtr xs); /*!< zs = -xs */
	void BLBlas_ZsEqReciprocalXsDc(BLPtr zs, BLCPtr xs); /*!< zs = 1.0/xs; scalar operation */
	void BLBlas_ZsEqZeroDc(BLPtr zs); /*!< zs = 0 */
	void BLBlas_ZsEqOneDc(BLPtr zs); /*! zs = 1 */
	float BLBlas_NormDc(BLCPtr xs); /*!< return norm(xs) */
#pragma endregion double complex operations

	PCBLBlasInterface BLBlas_GetInterface(BLTypes t);
#if defined(__cplusplus)
}
#endif
