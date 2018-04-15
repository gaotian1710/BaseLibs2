#include "stdafx.h"
#include "CppUnitTest.h"
#include "MatrixVectorData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(BLMatrix)
	{
		static const float tolF;
		static const double tolD;
	public:
		TEST_METHOD(UTMatrix_New)
		{
			BLRowColumn rc = { 3, 4 };
			PBLMatrix m = BLMatrix_New(rc, BLType_f);
			Assert::AreEqual(rc.row, m->rc.row);
			Assert::AreEqual(rc.column, m->rc.column);
			Assert::AreEqual((int)BLType_f, (int)(m->t));
			Assert::AreEqual(sizeof(float) * rc.row * rc.column,
				(size_t)(m->e.end.c - m->e.data.c), L"float data array size");
			BLMatrix_Delete(&m);
			m = BLMatrix_New(rc, BLType_d);
			Assert::AreEqual(sizeof(double) * BLRowColumn_Product(&rc),
				(size_t)(m->e.end.c - m->e.data.c), L"double data array size");
			BLMatrix_Delete(&m);
			m = BLMatrix_New(rc, BLType_fc);
			Assert::AreEqual(sizeof(_Fcomplex) * BLRowColumn_Product(&rc),
				(size_t)(m->e.end.c - m->e.data.c), L"float complex data array size");
			BLMatrix_Delete(&m);
			m = BLMatrix_New(rc, BLType_dc);
			Assert::AreEqual(sizeof(_Dcomplex) * BLRowColumn_Product(&rc),
				(size_t)(m->e.end.c - m->e.data.c), L"double complex data array size");
			BLMatrix_Delete(&m);
		}

		TEST_METHOD(UTMatrix_Unit)
		{
			BLRowColumn rc = { 3,3 };
			PBLMatrix m = BLMatrix_New(rc, BLType_f);
			int ierr = BLMatrix_Unit(m);
			Assert::AreEqual(0, ierr, L"BLMatrix_Unit(m) (float) return code");
			for (size_t i = 0; i < BLRowColumn_Product(&rc); i++)
			{
				Assert::AreEqual(MatrixVectorData::u3x3F[i], m->e.data.f[i], tolF,
					L"float element");
			}
			BLMatrix_Delete(&m);
			m = BLMatrix_New(rc, BLType_d);
			ierr = BLMatrix_Unit(m);
			Assert::AreEqual(0, ierr, L"BLMatrix_Unit(m) (double) return code");
			for (size_t i = 0; i < BLRowColumn_Product(&rc); i++)
			{
				Assert::AreEqual(MatrixVectorData::u3x3D[i], m->e.data.d[i], tolD,
					L"double element");
			}
			BLMatrix_Delete(&m);
			m = BLMatrix_New(rc, BLType_fc);
			ierr = BLMatrix_Unit(m);
			Assert::AreEqual(0, ierr, L"BLMatrix_Unit(m) (float complex) return code");
			for (size_t i = 0; i < BLRowColumn_Product(&rc); i++)
			{
				Assert::AreEqual(crealf(MatrixVectorData::u3x3Fc[i]), 
					crealf(m->e.data.fc[i]), tolF, L"float complex real part");
				Assert::AreEqual(cimagf(MatrixVectorData::u3x3Fc[i]),
					cimagf(m->e.data.fc[i]), tolF, L"float complex imaginary part");
			}
			BLMatrix_Delete(&m);
			m = BLMatrix_New(rc, BLType_dc);
			ierr = BLMatrix_Unit(m);
			Assert::AreEqual(0, ierr, L"BLMatrix_Unit(m) (double complex) return code");
			for (size_t i = 0; i < BLRowColumn_Product(&rc); i++)
			{
				Assert::AreEqual(creal(MatrixVectorData::u3x3Dc[i]),
					creal(m->e.data.dc[i]), tolD, L"double complex real part");
				Assert::AreEqual(cimag(MatrixVectorData::u3x3Dc[i]),
					cimag(m->e.data.dc[i]), tolD, L"double complex imaginary part");
			}
			BLMatrix_Delete(&m);
		}

		TEST_METHOD(UTMatrix_Transpose)
		{
			BLRowColumn rc = { 3, 4 };
			const float refSrc[] = {
				0.0f, 0.1f, 0.2f, 0.3f,
				1.0f, 1.1f, 1.2f, 1.3f,
				2.0f, 2.1f, 2.2f, 2.3f
			};
			const float refDst[] = {
				0.0f, 1.0f, 2.0f,
				0.1f, 1.1f, 2.1f,
				0.2f, 1.2f, 2.2f,
				0.3f, 1.3f, 2.3f
			};
			PBLMatrix m = BLMatrix_New(rc, BLType_f);
			BLRange range_m = BLRange_Init(m->e.data.f, m->e.end.f);
			BLCRange rangeSrc = BLRange_Init(refSrc, refSrc + ARRAYSIZE(refSrc));
			int ierr = BLBlas_ZEqXF(range_m, rangeSrc);
			Assert::AreEqual(0, ierr);
			PBLMatrix mt = BLMatrix_New(rc, BLType_f);
			ierr = BLMatrix_ZEqTransposeX(mt, m);
			for (size_t i = 0; i < ARRAYSIZE(refDst); i++)
			{
				Assert::AreEqual(refDst[i], mt->e.data.f[i], tolF);
			}
			BLMatrix_Delete(&m);
			BLMatrix_Delete(&mt);
		}

		TEST_METHOD(UTMatrix_AddEqX_SubEqX)
		{
			const float xsrc[] =
			{
				0.1f, 0.2f, 0.3f,
				1.1f, 1.2f, 1.3f
			};
			const float ysrc[] =
			{
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f
			};
			const float expectedXAddY[] =
			{
				1.1f, 2.2f, 3.3f,
				5.1f, 6.2f, 7.3f
			};
			BLRowColumn rc = { 2,3 };
			PBLMatrix x = BLMatrix_New(rc, BLType_f);
			PBLMatrix y = BLMatrix_New(rc, BLType_f);
			BLRange rangex = BLRange_Init(x->e.data.f, x->e.end.f);
			BLCRange rangexsrc = BLRange_Init(xsrc, xsrc + ARRAYSIZE(xsrc));
			int ierr = BLBlas_ZEqXF(rangex, rangexsrc);
			Assert::AreEqual((int)0, ierr, L"BLBlas_ZEqXF(rangex, rangexsrc) return value");
			BLRange rangey = BLRange_Init(y->e.data.f, y->e.end.f);
			BLCRange rangeysrc = BLRange_Init(ysrc, ysrc + ARRAYSIZE(ysrc));
			ierr = BLBlas_ZEqXF(rangey, rangeysrc);
			BLCRange crangey = BLRange_Init(rangey.scan.f, rangey.end.f);
			ierr = BLMatrix_ZAddEqX(x, y);
			Assert::AreEqual((int)0, ierr, L"BLMatrix_ZAddEqX(x, y) return value");
			for (size_t i = 0; i < ARRAYSIZE(expectedXAddY); i++)
			{
				Assert::AreEqual(expectedXAddY[i], *rangex.scan.f, tolF, L"BLMatrix_ZAddEqX() element comparison");
				rangex.scan.f++;
			}

			rangex.scan.f -= ARRAYSIZE(expectedXAddY);
			ierr = BLMatrix_ZSubEqX(x, y);
			Assert::AreEqual((int)0, ierr, L"BLMatrix_ZSubEqX(x, y) return value");
			for (size_t i = 0; i < ARRAYSIZE(ysrc); i++)
			{
				Assert::AreEqual(xsrc[i], *rangex.scan.f, tolF, L"BLMatrix_ZSubEqX() element comparison");
				rangex.scan.f++;
			}

			BLMatrix_Delete(&y);
			BLMatrix_Delete(&x);
		}

		TEST_METHOD(UTMatrix_MulEqXsF)
		{
			const float xsrc[] =
			{
				0.1f, 0.2f, 0.3f,
				1.1f, 1.2f, 1.3f
			};
			const float f = 2.0f;
			const float expectedResult[] =
			{
				f * xsrc[0], f * xsrc[1], f * xsrc[2],
				f * xsrc[3], f * xsrc[4], f * xsrc[5],
			};

			BLRowColumn rc = { 2, 3 };
			PBLMatrix x = BLMatrix_New(rc, BLType_f);
			BLRange rangex = BLRange_Init(x->e.data.f, x->e.end.f);
			BLCRange rangexsrc = BLRange_Init(xsrc, xsrc + ARRAYSIZE(xsrc));
			int ierr = BLBlas_ZEqXF(rangex, rangexsrc);
			ierr = BLMatrix_ZMulEqXsF(x, f);
			Assert::AreEqual((int)0, ierr, L"BLMatrix_ZMulEqXsF(x, f) return value");
			for (size_t i = 0; i < ARRAYSIZE(xsrc); i++)
			{
				Assert::AreEqual(expectedResult[i], *(rangex.scan.f + i), tolF);
			}
			BLMatrix_Delete(&x);
		}

		TEST_METHOD(UTMatrix_MultiplyTwoMatrices)
		{
			const float m0src[] =
			{
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f
			};
			const float m1src[] =
			{
				1.0f, 2.0f,
				4.0f, 5.0f,
				7.0f, 8.0f
			};
			const float productRef[] =
			{
				30.0f, 36.0f,
				66.0f, 81.0f
			};
			BLRowColumn rcm0 = { 2, 3 };
			BLRowColumn rcm1 = { 3, 2 };
			BLRowColumn rcm1t = { rcm1.column, rcm1.row };
			BLRowColumn rcProd = { 2, 2 };
			PBLMatrix m0 = BLMatrix_New(rcm0, BLType_f);
			PBLMatrix m1 = BLMatrix_New(rcm1, BLType_f);
			PBLMatrix wkm1t = BLMatrix_New(rcm1t, BLType_f);
			PBLMatrix prod = BLMatrix_New(rcProd, BLType_f);

			BLRange rangem0 = BLRange_Init(m0->e.data.f, m0->e.end.f);
			BLCRange rangem0src = BLRange_Init(m0src, m0src + ARRAYSIZE(m0src));
			int ierr = BLBlas_ZEqXF(rangem0, rangem0src);
			BLRange rangem1 = BLRange_Init(m1->e.data.f, m1->e.end.f);
			BLCRange rangem1src = BLRange_Init(m1src, m1src + ARRAYSIZE(m1src));
			ierr = BLBlas_ZEqXF(rangem1, rangem1src);

			ierr = BLMatrix_ZEqXMulY(prod, m0, m1, wkm1t);
			Assert::AreEqual((int)0, ierr, L"BLMatrix_ZEqXMulY(prod, m0, m1, wkm1t) return value");
			const float* pf = prod->e.data.f;
			const float* pfRef = productRef;
			for (size_t row = 0; row < prod->rc.row; row++)
			{
				for (size_t column = 0; column < prod->rc.column; column++)
				{
					Assert::AreEqual(*pfRef++, *pf++, tolF, L"element comparison");
				}
			}
			BLMatrix_Delete(&wkm1t);
			BLMatrix_Delete(&prod);
			BLMatrix_Delete(&m1);
			BLMatrix_Delete(&m0);
		}

		TEST_METHOD(UTMatrix_CopySubmatrix)
		{
			BLRowColumn rcsub = { 2, 3 };
			PBLMatrix psub = BLMatrix_New(rcsub, BLType_f);
			{
				BLRange rangeDst = BLRange_Init(psub->e.data.c, psub->e.end.c);
				BLCRange rangeSrc = BLRange_Init(
					MatrixVectorData::a2x3F,
					MatrixVectorData::a2x3F + BLRowColumn_Product(&rcsub)
				);
				int ierr = BLBlas_ZEqXF(rangeDst, rangeSrc);
				Assert::AreEqual(0, ierr, L"initializing submatrix psub");
			}
			size_t k = 0;
			BLRowColumn rc = { 4, 5 };
			PBLMatrix p = BLMatrix_New(rc, BLType_f);
			int ierr = BLMatrix_Zero(p);
			BLRowColumn rc1x1 = { 1, 1 };
			BLRowColumn rc1x2 = { 1, 2 };
			BLRowColumn rc0 = { 0, 0 };
			ierr = BLMatrix_Copy(p, rc1x1, psub, rc0, psub->rc);
			Assert::AreEqual(0, ierr, L"BLMatrix_Copy() return code 1");
			k = 0;
			for (size_t i = 0; i < p->rc.row; i++)
			{
				for (size_t j = 0; j < p->rc.column; j++)
				{
					Assert::AreEqual(MatrixVectorData::a4x5F[k], p->e.data.f[k], tolF,
						L"element comparison 1");
					k++;
				}
			}
			ierr = BLMatrix_Zero(p);
			ierr = BLMatrix_Copy(p, rc1x1, psub, rc1x1, rc1x2);
			Assert::AreEqual(0, ierr, L"BLMatrix_Copy() return code 2");
			k = 0;
			{
				for (size_t j = 0; j < p->rc.column; j++)
				{
					Assert::AreEqual(MatrixVectorData::a4x5F2[k], p->e.data.f[k], tolF,
						L"element comparison 1");
					k++;
				}
			}
			BLMatrix_Delete(&p);
			BLMatrix_Delete(&psub);
		}

		TEST_METHOD(UTMatrix_InvertF)
		{
			// get original matrix
			BLRowColumn rcorg = { 3, 3 };
			PBLMatrix porg = BLMatrix_New(rcorg, BLType_f);
			{
				BLRange rangeOrg = BLRange_Init(porg->e.data.f, porg->e.end.f);
				BLCRange rangeSrc = BLRange_Init(MatrixVectorData::a3x3F, MatrixVectorData::a3x3F + BLRowColumn_Product(&rcorg));
				Assert::AreEqual(0, BLBlas_ZEqXF(rangeOrg, rangeSrc), L"provisioning porg");
			}

			// prepare invert(porg) recipient
			PBLMatrix pinv = BLMatrix_New(rcorg, porg->t);
			{
				// prepare work matrix
				BLRowColumn rcwk = { rcorg.row, rcorg.column * 2 };
				PBLMatrix pwk = BLMatrix_New(rcwk, porg->t);

				// calculate invert
				Assert::AreEqual(0, BLMatrix_ZEqInvertX(pinv, porg, pwk), L"BLMatrix_New(rcwk, porg->t) return code");

				// prepare check matrix which is the product of porg * pwk.
				PBLMatrix pcheck = BLMatrix_New(rcorg, porg->t);
				PBLMatrix pwk3x3 = BLMatrix_New(rcorg, porg->t); // wokr matrix for matrix multiplying operation
				Assert::AreEqual(0, BLMatrix_ZEqXMulY(pcheck, porg, pinv, pwk3x3), L"BLMatrix_ZEqXMulY(pcheck, porg, pinv) return code");

				// compare the check matrix and a unit matrix
				size_t k = 0;
				for (size_t row = 0; row < rcorg.row; row++)
				{
					for (size_t column = 0; column < rcorg.column; column++)
					{
						Assert::AreEqual(
							MatrixVectorData::u3x3F[k],
							pcheck->e.data.f[k],
							tolF,
							L"check matrix element comparison"
						);
						k++;
					}
				}
			}
		}

		TEST_METHOD(UTMatrix_InvertFc)
		{
			// get original matrix
			BLRowColumn rcorg = { 3, 3 };
			PBLMatrix porg = BLMatrix_New(rcorg, BLType_fc);
			{
				BLRange rangeOrg = BLRange_Init(porg->e.data.fc, porg->e.end.fc);
				BLCRange rangeSrc = BLRange_Init(MatrixVectorData::a3x3Fc, MatrixVectorData::a3x3Fc + BLRowColumn_Product(&rcorg));
				Assert::AreEqual(0, BLBlas_ZEqXFc(rangeOrg, rangeSrc), L"provisioning porg");
			}

			// prepare invert(porg) recipient
			PBLMatrix pinv = BLMatrix_New(rcorg, porg->t);
			{
				// prepare work matrix
				BLRowColumn rcwk = { rcorg.row, rcorg.column * 2 };
				PBLMatrix pwk = BLMatrix_New(rcwk, porg->t);

				// calculate invert
				Assert::AreEqual(0, BLMatrix_ZEqInvertX(pinv, porg, pwk), L"BLMatrix_New(rcwk, porg->t) return code");

				// prepare check matrix which is the product of porg * pwk.
				PBLMatrix pcheck = BLMatrix_New(rcorg, porg->t);
				PBLMatrix pwk3x3 = BLMatrix_New(rcorg, porg->t); // wokr matrix for matrix multiplying operation
				Assert::AreEqual(0, BLMatrix_ZEqXMulY(pcheck, porg, pinv, pwk3x3), L"BLMatrix_ZEqXMulY(pcheck, porg, pinv) return code");

				// compare the check matrix and a unit matrix
				size_t k = 0;
				for (size_t row = 0; row < rcorg.row; row++)
				{
					for (size_t column = 0; column < rcorg.column; column++)
					{
						Assert::AreEqual(
							crealf(MatrixVectorData::u3x3Fc[k]),
							crealf(pcheck->e.data.fc[k]),
							tolF,
							L"check matrix element real part comparison"
						);
						Assert::AreEqual(
							cimagf(MatrixVectorData::u3x3Fc[k]),
							cimagf(pcheck->e.data.fc[k]),
							tolF,
							L"check matrix element imaginary part comparison"
						);
						k++;
					}
				}
			}
		}

		TEST_METHOD(UTMatrix_InvertDc)
		{
			// get original matrix
			BLRowColumn rcorg = { 3, 3 };
			PBLMatrix porg = BLMatrix_New(rcorg, BLType_dc);
			{
				BLRange rangeOrg = BLRange_Init(porg->e.data.dc, porg->e.end.dc);
				BLCRange rangeSrc = BLRange_Init(MatrixVectorData::a3x3Dc, MatrixVectorData::a3x3Dc + BLRowColumn_Product(&rcorg));
				Assert::AreEqual(0, BLBlas_ZEqXFc(rangeOrg, rangeSrc), L"provisioning porg");
			}

			// prepare invert(porg) recipient
			PBLMatrix pinv = BLMatrix_New(rcorg, porg->t);
			{
				// prepare work matrix
				BLRowColumn rcwk = { rcorg.row, rcorg.column * 2 };
				PBLMatrix pwk = BLMatrix_New(rcwk, porg->t);

				// calculate invert
				Assert::AreEqual(0, BLMatrix_ZEqInvertX(pinv, porg, pwk), L"BLMatrix_New(rcwk, porg->t) return code");

				// prepare check matrix which is the product of porg * pwk.
				PBLMatrix pcheck = BLMatrix_New(rcorg, porg->t);
				PBLMatrix pwk3x3 = BLMatrix_New(rcorg, porg->t); // wokr matrix for matrix multiplying operation
				Assert::AreEqual(0, BLMatrix_ZEqXMulY(pcheck, porg, pinv, pwk3x3), L"BLMatrix_ZEqXMulY(pcheck, porg, pinv) return code");

				// compare the check matrix and a unit matrix
				size_t k = 0;
				for (size_t row = 0; row < rcorg.row; row++)
				{
					for (size_t column = 0; column < rcorg.column; column++)
					{
						Assert::AreEqual(
							creal(MatrixVectorData::u3x3Dc[k]),
							creal(pcheck->e.data.dc[k]),
							tolD,
							L"check matrix element real part comparison"
						);
						Assert::AreEqual(
							cimag(MatrixVectorData::u3x3Dc[k]),
							cimag(pcheck->e.data.dc[k]),
							tolD,
							L"check matrix element imaginary part comparison"
						);
						k++;
					}
				}
			}
		}
	};

	const float BLMatrix::tolF = 1.0e-5f;
	const double BLMatrix::tolD = 1.0e-10;
}