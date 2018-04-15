#pragma once
/*!
\struct BLRowColumn
*/
typedef struct {
	size_t row, column;
} BLRowColumn, *PBLRowColumn;

typedef const BLRowColumn* PCBLRowColumn;

/*!
\struct BLMatrix
*/
typedef struct {
	BLTypes t;
	BLRowColumn rc;
	BLArray e;
} BLMatrix, *PBLMatrix;

typedef const BLMatrix *PCBLMatrix;

#if defined(__cplusplus)
extern "C" {
#endif
	inline size_t BLRowColumn_Product(PCBLRowColumn rc)
	{
		return rc->row * rc->column;
	}

	inline bool BLRowColumn_Eq(PCBLRowColumn rc0, PCBLRowColumn rc1)
	{
		return (rc0->row == rc1->row) && (rc0->column == rc1->column);
	}

	inline bool BLRowColumn_IsLE(PCBLRowColumn rcInner, PCBLRowColumn rcOuter)
	{
		return (rcInner->row <= rcOuter->row && rcInner->column <= rcOuter->column);
	}

	inline bool BLRowColumn_IsLT(PCBLRowColumn rcInner, PCBLRowColumn rcOuter)
	{
		return (rcInner->row < rcOuter->row && rcInner->column < rcOuter->column);
	}

	inline size_t BLRowColumn_SquareSize(PCBLRowColumn rc)
	{
		return rc->row * rc->column;
	}

	inline bool BLRowColumn_IsNotSquare(PCBLRowColumn rc)
	{
		return (rc->row == 0) || (rc->row != rc->column);
	}

	inline BLRowColumn BLRowColumn_Add(PCBLRowColumn rc0, PCBLRowColumn rc1)
	{
		BLRowColumn rc = { rc0->row + rc1->row, rc0->column + rc1->column };
		return rc;
	}

	inline void BLRowColumn_AddEq(PBLRowColumn rcDst, PCBLRowColumn rcSrc)
	{
		rcDst->row += rcSrc->row;
		rcDst->column += rcSrc->column;
	}

	inline int BLRowColumn_SubEq(PBLRowColumn rcDst, PCBLRowColumn rcSrc)
	{
		int ierr = ERANGE;
		if (rcDst->row >= rcSrc->row && rcDst->column >= rcSrc->column)
		{
			rcDst->row -= rcSrc->row;
			rcDst->column -= rcSrc->column;
			ierr = 0;
		}
		return ierr;
	}

	/*!
	\brief create a new object.
	\param rc [in] row and column
	\param t [in] element number type
	\return pointer to the new object
	*/
	PBLMatrix BLMatrix_New(BLRowColumn rc, BLTypes t);

	/*!
	\brief delete an object
	\param [in,out] pointer pointer to the object to delete
	*/
	void BLMatrix_Delete(PBLMatrix* pp);

	/*!
	\brief fill the matrix with a unit matrix
	\param p [out] the matrix to fill
	*/
	int BLMatrix_Unit(PBLMatrix p);

	/*!
	\brief fill the matrix with zero
	\param p [out] the matrix to fill
	*/
	int BLMatrix_Zero(PBLMatrix p);

	/*!
	\brief z += x
	\param z [in,out] L.H.S.
	\param x [in] R.H.S.
	\return error code (unix style errno)
	*/
	int BLMatrix_ZAddEqX(PBLMatrix z, PCBLMatrix x);

	/*!
	\brief z -= x
	\param z [in,out] L.H.S.
	\param x [in] R.H.S.
	\return error code (unix style errno)
	*/
	int BLMatrix_ZSubEqX(PBLMatrix z, PCBLMatrix x);

	/*!
	\brief z *= xs;
	\param z [in,out] L.H.S.
	\param xs [in] R.H.S, float number
	\return error code (unix style errno)
	*/
	int BLMatrix_ZMulEqXsF(PBLMatrix z, float xs);

	/*!
	\brief z *= xs;
	\param z [in,out] L.H.S.
	\param xs [in] R.H.S, double number
	\return error code (unix style errno)
	*/
	int BLMatrix_ZMulEqXsD(PBLMatrix z, double xs);

	/*!
	\brief z *= xs;
	\param z [in,out] L.H.S.
	\param xs [in] R.H.S, _Fcomplex number
	\return error code (unix style errno)
	*/
	int BLMatrix_ZMulEqXsFc(PBLMatrix z, _Fcomplex xs);

	/*!
	\brief z *= xs;
	\param z [in,out] L.H.S.
	\param xs [in] R.H.S, _Dcomplex number
	\return error code (unix style errno)
	*/
	int BLMatrix_ZMulEqXsDc(PBLMatrix z, _Dcomplex xs);

	/*!
	\brief z = transpose(x)
	\param z [out] L.H.S.
	\param x [in] R.H.S.
	\return error code (unix style errno)
	*/
	int BLMatrix_ZEqTransposeX(PBLMatrix z, PCBLMatrix x);

	/*!
	\brief z = invert(x)
	\param z [out] L.H.S.
	\param x [in] R.H.S.
	\param wk working matrix
	\return error code (unix style errno)
	*/
	int BLMatrix_ZEqInvertX(PBLMatrix z, PCBLMatrix x, PBLMatrix wk);

	/*!
	\brief z = x + y;
	\param z [out] L.H.S.
	\param x [in]
	\param y [in]
	\return error code (unix style errno)
	*/
	int BLMatrix_ZEqXAddY(PBLMatrix z, PCBLMatrix x, PCBLMatrix y);

	/*!
	\brief z = x - y;
	\param z [out] L.H.S.
	\param x [in]
	\param y [in]
	\return error code (unix style errno)
	*/
	int BLMatrix_ZEqXSubY(PBLMatrix z, PCBLMatrix x, PCBLMatrix y);

	/*!
	\brief z = x * y;
	\param z [out] L.H.S.
	\param x [in]
	\param y [in]
	\param wkyt work matrix to put the transpose of y.
	\return error code (unix style errno)
	*/
	int BLMatrix_ZEqXMulY(PBLMatrix z, PCBLMatrix x, PCBLMatrix y, PBLMatrix wkyt);

	/*!
	\brief copy submatrix to submatrix
	\param z [out] copy destination
	\param zo [in] row,column offset of copy destination
	\param x [in] copy source
	\param xo [in] row,column offset of copy source
	\param xs [in] row,column size of copy source
	\return error code (unix style errno)
	*/
	int BLMatrix_Copy(PBLMatrix z, BLRowColumn zo, PCBLMatrix x, BLRowColumn xo, BLRowColumn xs);
#if defined(__cplusplus)
}
#endif
