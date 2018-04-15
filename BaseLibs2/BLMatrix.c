#include "stdafx.h"
#include "BLTypes.h"
#include "BLError.h"
#include "BLArray.h"
#include "BLBlas.h"
#include "BLMatrix.h"

#define BLMatrix_CheckTypeBreak(m0, m1, ierr) \
if ((m0)->t != (m1)->t) \
{ \
	ierr = EINVAL; break; \
}

#define BLMatrix_CheckRowColumnBreak(m0, m1, ierr) \
if (((m0)->rc.row != (m1)->rc.row) || ((m0)->rc.column != (m1)->rc.column)) \
{ \
	ierr = ERANGE; break; \
}

#define BLMatrix_CheckBufferSizeBreak(m0, m1, ierr) \
if (BLRowColumn_SquareSize(&(m0->rc)) != BLRowColumn_SquareSize(&(m1->rc))) \
{ \
	ierr = ERANGE; break; \
}

#define BLMatrix_CheckIsNotSquareBreak(m0, ierr) \
if (BLRowColumn_IsNotSquare(&(m0->rc))) { \
	ierr = EINVAL; break; \
}

PBLMatrix BLMatrix_New(BLRowColumn rc, BLTypes t)
{
	size_t cbPureData = BLUnitSizes[t] * rc.row * rc.column;
	size_t cbAlloc = sizeof(BLMatrix) - sizeof(BLData1) + cbPureData;
	PBLMatrix p = (PBLMatrix)malloc(cbAlloc);
	if (p)
	{
		p->rc = rc;
		p->e.end.c = p->e.data.c + cbPureData;
		p->t = t;
		if (BLMatrix_Zero(p))
		{
			free(&p);
		}
	}
	return p;
}

void BLMatrix_Delete(PBLMatrix * pp)
{
	if (pp && *pp)
	{
		free((void*)(*pp));
		*pp = NULL;
	}
}

int BLMatrix_SetOne(BLPtr p, BLTypes t)
{
	int ierr = 0;
	switch (t)
	{
	case BLType_f:
		*p.f = 1.0f;
		break;
	case BLType_d:
		*p.d = 1.0;
		break;
	case BLType_fc:
		*p.fc = _FCOMPLEX_(1.0f, 0.0f);
		break;
	case BLType_dc:
		*p.dc = _DCOMPLEX_(1.0, 0.0);
		break;
	default:
		ierr = EINVAL;
		break;
	}
	return ierr;
}

int BLMatrix_Unit(PBLMatrix p)
{
	int ierr = ERANGE;
	do {
		BLMatrix_CheckIsNotSquareBreak(p, ierr);
		PCBLBlasInterface blas = BLBlas_GetInterface(p->t);
		BLRange range = BLRange_Init(p->e.data.f, p->e.end.f);
		ierr = blas->fillZeros(range);
		if (ierr) break;

		// set diagonal elements to 1.0
		BLPtr diagonalElement = { p->e.data.c };
		size_t step = BLUnitSizes[p->t] * (p->rc.column + 1);
		for (size_t row = 0; row < p->rc.row; row++, diagonalElement.c += step)
		{
			blas->zsEqOne(diagonalElement);
		}
	} while (false);
	return ierr;
}

int BLMatrix_Zero(PBLMatrix p)
{
	BLRange range = BLRange_Init(p->e.data.c, p->e.end.c);
	return BLBlas_GetInterface(p->t)->fillZeros(range);
}

int BLMatrix_ZAddEqX(PBLMatrix z, PCBLMatrix x)
{
	int ierr = 0;
	do {
		BLMatrix_CheckRowColumnBreak(z, x, ierr);
		BLMatrix_CheckTypeBreak(z, x, ierr);

		BLRange rangez = BLRange_Init(z->e.data.c, z->e.end.c);
		BLCRange rangex = BLRange_Init(x->e.data.c, x->e.end.c);
		ierr = BLBlas_GetInterface(z->t)->zAddEqX(rangez, rangex);
	} while (false);
	return ierr;
}

int BLMatrix_ZSubEqX(PBLMatrix z, PCBLMatrix x)
{
	int ierr = 0;
	do {
		BLMatrix_CheckRowColumnBreak(z, x, ierr);
		BLMatrix_CheckTypeBreak(z, x, ierr);

		BLRange rangez = BLRange_Init(z->e.data.c, z->e.end.c);
		BLCRange rangex = BLRange_Init(x->e.data.c, x->e.end.c);
		ierr = BLBlas_GetInterface(z->t)->zSubEqX(rangez, rangex);
	} while (false);
	return ierr;
}

int BLMatrix_ZMulEqXsF(PBLMatrix z, float xs)
{
	int ierr = 0;
	do {
		if (z->t != BLType_f)
		{
			ierr = EINVAL; break;
		}
		BLRange rangez = BLRange_Init(z->e.data.f, z->e.end.f);
		BLCPtr ptrxs = { (char*)&xs };
		ierr = BLBlas_GetInterface(z->t)->zMulEqXs(rangez, ptrxs);
	} while (false);
	return ierr;
}

//int BLMatrix_ZMulEqXsD(PBLMatrix z, double xs)
//{
//	int ierr = 0;
//	do {
//		if (z->t != BLType_d)
//		{
//			ierr = EINVAL; break;
//		}
//		BLRange rangez = BLRange_Init(z->e.data.f, z->e.end.f);
//		BLCPtr ptrxs = { (char*)&xs };
//		ierr = BLBlas_ZMulEqXsD(rangez, ptrxs);
//	} while (false);
//	return ierr;
//}

int BLMatrix_ZEqTransposeX(PBLMatrix z, PCBLMatrix x)
{
	int ierr = 0;
	do {
		// range and type check
		BLMatrix_CheckTypeBreak(z, x, ierr);
		BLMatrix_CheckBufferSizeBreak(z, x, ierr);

		PCBLBlasInterface blas = BLBlas_GetInterface(z->t);
		// transpose operation
		{
			size_t zCount = z->rc.column * z->rc.row;
			size_t xCount = x->rc.column * x->rc.row;
			if (zCount != xCount) return ERANGE;
			z->rc.row = x->rc.column;
			z->rc.column = x->rc.row;
			BLPtr pz = { z->e.data.c };
			BLCPtr px = { x->e.data.c };
			size_t unitSize = BLUnitSizes[x->t];
			size_t resetRowAndNextColumn = unitSize * (x->rc.row * x->rc.column - 1);
			size_t zNextRow = unitSize * z->rc.column;
			for (size_t row = 0; row < x->rc.row; row++)
			{
				for (size_t column = 0; column < x->rc.column; column++)
				{
					blas->zsEqConjXs(pz, px);
					px.c += unitSize;
					pz.c += zNextRow;
				}
				pz.c -= resetRowAndNextColumn;
			}
		}
	} while (false);
	return ierr;
}

size_t BLMatrix_FindPivotRow(PCBLMatrix m, size_t pvColumn, BLBlas_norm normfunc)
{
	size_t cbUnit = BLUnitSizes[m->t]; // byte count of unit element
	size_t cbMatrixWidth = cbUnit * m->rc.column;
	size_t rowPv = pvColumn; // pivot row number
	BLCPtr ptrPv =  // pivot element pointer
	{
		m->e.data.c + cbMatrixWidth * rowPv + cbUnit * pvColumn
	};
	float normPv = normfunc(ptrPv); // norm of pivot element
	for (size_t row = rowPv+1; row < m->rc.row; row++)
	{
		ptrPv.c += cbMatrixWidth; // update pivot element pointer
		float normPvNew = normfunc(ptrPv); // calculate the norm of the new pivot element
		// update normPv and rowPv if the new pivot norm is greater than the current one.
		if (normPv < normPvNew)
		{
			normPv = normPvNew;
			rowPv = row;
		}
	}
	return rowPv; // return the row number of with the largest norm pivot.
}

int BLMatrix_ZEqInvertX(PBLMatrix z, PCBLMatrix x, PBLMatrix wk)
{
	int ierr = 0;
	do {
		// range and type check
		BLMatrix_CheckTypeBreak(z, x, ierr);
		BLMatrix_CheckTypeBreak(z, wk, ierr);
		BLMatrix_CheckIsNotSquareBreak(z, ierr);
		BLMatrix_CheckIsNotSquareBreak(x, ierr);
		BLMatrix_CheckRowColumnBreak(z, x, ierr);
		if ((wk->rc.row != z->rc.row) || (wk->rc.column != 2 * (z->rc.column)))
		{
			ierr = ERANGE; break;
		}
		PCBLBlasInterface blas = BLBlas_GetInterface(z->t);
		if (blas == NULL)
		{
			ierr = EINVAL; break;
		}
		size_t cbUnit = BLUnitSizes[x->t];

		// initialize wk
		BLRowColumn oRightHalf = { 0, z->rc.column }; // offset of the right half of wk
		BLRowColumn o0 = { 0, 0 };
		{
			ierr = BLMatrix_Unit(z); // fill z with a unit matarix
			if (ierr) break;
			ierr = BLMatrix_Copy(wk, o0, x, o0, x->rc); // copy x to wk left half
			if (ierr) break;
			ierr = BLMatrix_Copy(wk, oRightHalf, z, o0, z->rc); // fill wk right half with a unit matrix
			if (ierr) break;
		}

		{ // row operation over wk
			size_t cbWkWidth = cbUnit * wk->rc.column; // wk width counted in bytes
			BLData1 normalizer = { ' ' }; // generic scalar work buffer
			BLPtr ptrNormalizer = { normalizer.c };
			BLCPtr refptrNormalizer = { normalizer.c };
			size_t cbActiveWidth = cbWkWidth;
			for (size_t row = 0; row < wk->rc.row; row++, cbActiveWidth -= cbUnit)
			{
				BLPtr ptrPvRow = { wk->e.data.c + cbWkWidth * row };
				// find pivot row candidate
				size_t pvRowNew = BLMatrix_FindPivotRow(wk, row, blas->norm);

				BLPtr ptrRow0 = { wk->e.data.c + row * cbWkWidth }; // pivot row beginning element
				// active range of the pivot row
				BLRange rangeRow0 = BLRange_Init(ptrRow0.c + cbUnit * row, ptrRow0.c + cbWkWidth);
				// swap if the pivot row candidate and the current pivot row are different
				if (pvRowNew != row)
				{
					BLPtr ptrRow1 = { wk->e.data.c + pvRowNew * cbWkWidth }; // another row beginning element
					// active range of another row; new and better pivot row
					BLRange rangeRow1 = BLRange_Init(ptrRow1.c + cbUnit * row, ptrRow1.c + cbWkWidth);
					ierr = blas->swap(rangeRow0, rangeRow1);
					if (ierr) break;
				}
				// normalize pivot row
				BLCPtr pvEle = { rangeRow0.scan.c };
				blas->zsEqReciprocalXs(ptrNormalizer, pvEle); // get reciprocal of the pivot element
				ierr = blas->zMulEqXs(rangeRow0, refptrNormalizer); // normalize the pivot row active range
				
				// delete pivot column
				BLCPtr eleToDelete = { wk->e.data.c + cbUnit * row }; // 1st row active range beginning
				BLCRange refrangeRow0 = BLRange_Init(rangeRow0.scan.c, rangeRow0.end.c); // pivot row active range as const parameters
				for (size_t rowToDelete = 0; rowToDelete < wk->rc.row; rowToDelete++, eleToDelete.c += cbWkWidth)
				{
					if (row == rowToDelete) continue;
					blas->zsEqNegateXs(ptrNormalizer, eleToDelete);
					BLRange rangeToDelete = BLRange_Init(eleToDelete.c, eleToDelete.c + cbActiveWidth);
					ierr = blas->zAddEqXMulYs(rangeToDelete, refrangeRow0, refptrNormalizer);
					if (ierr) break;
				}
			}
		}
		if (ierr) break;

		// copy wk right half to z
		ierr = BLMatrix_Copy(z, o0, wk, oRightHalf, z->rc);
	} while (false);
	return ierr;
}

int BLMatrix_ZEqXAddY(PBLMatrix z, PCBLMatrix x, PCBLMatrix y)
{
	int ierr = 0;
	do {
		// check types and sizes
		BLMatrix_CheckTypeBreak(z, x, ierr);
		BLMatrix_CheckTypeBreak(z, y, ierr);
		BLMatrix_CheckRowColumnBreak(z, x, ierr);
		BLMatrix_CheckRowColumnBreak(z, y, ierr);
		PCBLBlasInterface blas = BLBlas_GetInterface(x->t);
		if (blas == NULL)
		{
			ierr = EINVAL; break;
		}

		// add operation
		{
			BLRange rangez = BLRange_Init(z->e.data.c, z->e.end.c);
			BLCRange rangex = BLRange_Init(x->e.data.c, x->e.end.c);
			BLCRange rangey = BLRange_Init(y->e.data.c, y->e.end.c);
			ierr = blas->zEqXAddY(rangez, rangex, rangey);
		}
	} while (false);
	return ierr;
}

int BLMatrix_ZEqXSubY(PBLMatrix z, PCBLMatrix x, PCBLMatrix y)
{
	int ierr = 0;
	do {
		// check types and sizes
		BLMatrix_CheckTypeBreak(z, x, ierr);
		BLMatrix_CheckTypeBreak(z, y, ierr);
		BLMatrix_CheckRowColumnBreak(z, x, ierr);
		BLMatrix_CheckRowColumnBreak(z, y, ierr);
		PCBLBlasInterface blas = BLBlas_GetInterface(x->t);
		if (blas == NULL)
		{
			ierr = EINVAL; break;
		}

		// add operation
		{
			BLRange rangez = BLRange_Init(z->e.data.c, z->e.end.c);
			BLCRange rangex = BLRange_Init(x->e.data.c, x->e.end.c);
			BLCRange rangey = BLRange_Init(y->e.data.c, y->e.end.c);
			ierr = blas->zEqXSubY(rangez, rangex, rangey);
		}
	} while (false);
	return ierr;
}

int BLMatrix_ZEqXMulY(PBLMatrix z, PCBLMatrix x, PCBLMatrix y, PBLMatrix wkyt)
{
	int ierr = 0;
	size_t cbUnit = BLUnitSizes[z->t];
	size_t cbXWidth = cbUnit * x->rc.column;
	do {
		// check types
		BLMatrix_CheckTypeBreak(z, x, ierr);
		BLMatrix_CheckTypeBreak(z, y, ierr);
		BLMatrix_CheckTypeBreak(z, wkyt, ierr);
		BLMatrix_CheckTypeBreak(z, x, ierr);

		// check rows and columns
		bool rowsAndColumnsConsistent =
			z->rc.row == x->rc.row &&
			z->rc.column == y->rc.column &&
			x->rc.column == y->rc.row &&
			y->rc.row == wkyt->rc.column &&
			y->rc.column == wkyt->rc.row;
		if (!rowsAndColumnsConsistent)
		{
			ierr = ERANGE; break;
		}
		PCBLBlasInterface blas = BLBlas_GetInterface(x->t);
		if (blas == NULL)
		{
			ierr = EINVAL; break;
		}

		// wkyt = transpose(y)
		ierr = BLMatrix_ZEqTransposeX(wkyt, y);

		// calculate products
		BLPtr ptrz = { z->e.data.c };
		BLCPtr ptrx = { x->e.data.c };
		for (size_t zrow = 0; zrow < z->rc.row; zrow++)
		{
			BLCRange rangex = BLRange_Init(ptrx.c, ptrx.c + cbXWidth);
			BLCPtr ptryt = { wkyt->e.data.c };
			for (size_t zcolumn = 0; zcolumn < z->rc.column; zcolumn++)
			{
				BLCRange rangeyt = BLRange_Init(ptryt.c, ptryt.c + cbXWidth);
				ierr = blas->zEqXInnerProductY(ptrz, rangex, rangeyt);
				if (ierr) break;
				ptrz.c += cbUnit;
				ptryt.c += cbXWidth;
			}
			if (ierr) break;
			ptrx.c += cbXWidth;
		}
	} while (false);
	return ierr;
}

int BLMatrix_Copy(PBLMatrix z, BLRowColumn zo, PCBLMatrix x, BLRowColumn xo, BLRowColumn xs)
{
	int ierr = 0;
	BLRowColumn rcZEnd = BLRowColumn_Add(&zo, &xs);
	BLRowColumn rcXEnd = BLRowColumn_Add(&xo, &xs);
	size_t cbUnit = BLUnitSizes[z->t];
	size_t cbCopyWidth = cbUnit * xs.column;
	size_t cbZWidth = cbUnit * z->rc.column;
	size_t cbXWidth = cbUnit * x->rc.column;
	do {
		// type check
		BLMatrix_CheckTypeBreak(z, x, ierr);
		// offset and size check
		if ((!BLRowColumn_IsLT((PCBLRowColumn)&zo, (PCBLRowColumn)&(z->rc))) ||
			(!BLRowColumn_IsLT((PCBLRowColumn)&xo, (PCBLRowColumn)&(x->rc))) ||
			(!BLRowColumn_IsLE((PCBLRowColumn)&rcZEnd, (PCBLRowColumn)&(z->rc))) ||
			(!BLRowColumn_IsLE((PCBLRowColumn)&rcXEnd, (PCBLRowColumn)&(x->rc))))
		{
			ierr = ERANGE; break;
		}

		// row-by-row copy operation
		size_t rowz = zo.row;
		size_t rowx = xo.row;
		for (; rowz < rcZEnd.row; rowz++, rowx++)
		{
			BLPtr zBegin = { z->e.data.c + cbUnit * zo.column + rowz * cbZWidth };
			BLRange rangez = BLRange_Init(zBegin.c, zBegin.c + cbCopyWidth);
			BLCPtr xBegin = { x->e.data.c + cbUnit * xo.column + rowx * cbXWidth };
			BLCRange rangex = BLRange_Init(xBegin.c, xBegin.c + cbCopyWidth);
			ierr = BLBlas_ZEqXF(rangez, rangex);
			if (ierr) break;
		}
	} while (false);
	return ierr;
}

