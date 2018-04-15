#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(BLBlas)
	{
		static const int ccBuffer = 256;
		static wchar_t buffer[ccBuffer];
		static const float tolF;
		static const double tolD;
	public:
		/*!
		\brief test range check macro for 1 array parameter operation like z = 0.0f;
		*/
		TEST_METHOD(UTBlas_RangeCheck1)
		{
			float f = .0f;
			{
				BLRange range = BLRange_Init(&f, &f);
				int ierr = BLRange_Check1(&range, BLType_f);
				Assert::AreEqual((int)ERANGE, ierr, L"BLRange_Check1(), returns ERANGE");
			}
			{
				uint16_t ui16;
				BLRange range = BLRange_Init(&ui16, &ui16 + 1);
				int ierr = BLRange_Check1(&range, BLType_f);
				Assert::AreEqual((int)ERANGE, ierr, L"BLRange_Check1(), returns ERANGE, unit size is too small.");
			}
			{
				BLRange range = BLRange_Init(&f, &f + 1);
				int ierr = BLRange_Check1(&range, BLType_f);
				Assert::AreEqual((int)0, ierr, L"BLRange_Check1(), returns 0");
			}
		}

		/*!
		\brief test range check macro for 2 array parameter operatioin like z += x;
		*/
		TEST_METHOD(UTBlas_RangeCheck2)
		{
			float f0[] = { 0.0f, 1.0f, 2.0f, 3.0f };
			float f1[] = { 1.0f, 2.0f, 3.0f, 4.0f };
			{
				BLRange range0 = BLRange_Init(f0, f0 + ARRAYSIZE(f0));
				BLCRange range1 = BLCRange_Init(f1, f1 + ARRAYSIZE(f1));
				int ierr = BLRange_Check2(&range0, &range1, BLType_f);
				Assert::AreEqual((int)0, ierr, L"BRange_Check2(), return 0");
			}
			{
				BLRange range0 = BLRange_Init(f0, f0 + ARRAYSIZE(f0));
				BLCRange range1 = BLCRange_Init(f1, f1 + ARRAYSIZE(f1)-1);
				int ierr = BLRange_Check2(&range0, &range1, BLType_f);
				Assert::AreEqual((int)ERANGE, ierr, L"BRange_Check2(), return ERANGE");
			}
		}

		/*!
		\brief test range check macro for 3 array parameter operations like z = x + y;
		*/
		TEST_METHOD(UTBlas_RangeCheck3)
		{
			float f0[] = { 0.0f, 1.0f, 2.0f, 3.0f };
			const float f1[] = { 1.0f, 2.0f, 3.0f, 4.0f };
			const float f2[] = { 2.0f, 2.0f, 3.0f, 4.0f };
			{
				BLRange range0 = BLRange_Init(f0, f0 + ARRAYSIZE(f0));
				BLCRange range1 = BLCRange_Init(f1, f1 + ARRAYSIZE(f1));
				BLCRange range2 = BLCRange_Init(f2, f2 + ARRAYSIZE(f2));
				int ierr = BLRange_Check3(&range0, &range1, &range2, BLType_f);
				Assert::AreEqual((int)0, ierr, L"BRange_Check3(), return 0");
			}
			{
				BLRange range0 = BLRange_Init(f0, f0 + ARRAYSIZE(f0));
				BLCRange range1 = BLCRange_Init(f1, f1 + ARRAYSIZE(f1));
				BLCRange range2 = BLCRange_Init(f2, f2 + ARRAYSIZE(f2) + 1);
				int ierr = BLRange_Check3(&range0, &range1, &range2, BLType_f);
				Assert::AreEqual((int)ERANGE, ierr, L"BRange_Check3(), return ERANGE");
			}
		}

		/*!
		\brief test 1 dependent varialble,0 independent varialble operations,like z = 1.0f;
		*/
		TEST_METHOD(UTBlas_1v0c_float)
		{
			PBLArray p = BLArray_New(4, BLType_f);
			//BLRange range = { { p->data.c }, p->end };
			BLRange range = BLRange_Init(p->data.f, p->end.f);
			BLBlas_ZEqOneF(range);
			Assert::AreEqual(1.0f, p->data.f[0], tolF, L"f[0]=1.0f");
			Assert::AreEqual(1.0f, p->data.f[3], tolF, L"f[3]=1.0f");
			BLBlas_ZEqMinusOneF(range);
			Assert::AreEqual(-1.0f, p->data.f[0], tolF, L"f[0]=-1.0f");
			Assert::AreEqual(-1.0f, p->data.f[3], tolF, L"f[3]=-1.0f");
			BLBlas_ZEqZeroF(range);
			Assert::AreEqual(0.0f, p->data.f[0], tolF, L"f[0]=0.0f");
			Assert::AreEqual(0.0f, p->data.f[3], tolF, L"f[3]=0.0f");
			BLArray_Delete(&p);
		}

		/*!
		\brief test 1 dependent variable, 1 independent varialble operations, like z += x;
		*/
		TEST_METHOD(UTBlas_1v1c_float)
		{
			static const float fSrc[] = { 0.0f, 1.0f, 2.0f, 3.0f };
			static const float fSrc2[] = { 3.0f, 2.0f, 1.0f, 0.0f };
			static const float result2[] = { 0.0f, 2.0f, 2.0f, 0.0f };
			PBLArray pDst = BLArray_New(4, BLType_f);
			BLRange rangeDst = BLRange_Init(pDst->data.f, pDst->end.f);
			BLCRange rangeSrc = BLCRange_Init(fSrc, fSrc + ARRAYSIZE(fSrc));
			
			BLBlas_ZEqXF(rangeDst, rangeSrc);
			Assert::AreEqual(fSrc[0], pDst->data.f[0], tolF, L"z = x [0]");
			Assert::AreEqual(fSrc[1], pDst->data.f[1], tolF, L"z = x [1]");
			Assert::AreEqual(fSrc[2], pDst->data.f[2], tolF, L"z = x [2]");
			Assert::AreEqual(fSrc[3], pDst->data.f[3], tolF, L"z = x [3]");

			BLCRange rangeSrc2 = BLCRange_Init(fSrc2, fSrc2 + ARRAYSIZE(fSrc));
			BLBlas_ZMulEqXF(rangeDst, rangeSrc2);
			Assert::AreEqual(result2[0], pDst->data.f[0], tolF, L"z *= x [0]");
			Assert::AreEqual(result2[1], pDst->data.f[1], tolF, L"z *= x [1]");
			Assert::AreEqual(result2[2], pDst->data.f[2], tolF, L"z *= x [2]");
			Assert::AreEqual(result2[3], pDst->data.f[3], tolF, L"z *= x [3]");

			BLBlas_ZDivEqXF(rangeDst, rangeSrc2);
			Assert::AreEqual(fSrc[0], pDst->data.f[0], tolF, L"z /= x [0]");
			Assert::AreEqual(fSrc[1], pDst->data.f[1], tolF, L"z /= x [1]");
			Assert::AreEqual(fSrc[2], pDst->data.f[2], tolF, L"z /= x [2]");

			BLBlas_ZSubEqXF(rangeDst, rangeSrc);
			Assert::AreEqual(0.0f, pDst->data.f[0], tolF, L"z -= x [0]");
			Assert::AreEqual(0.0f, pDst->data.f[1], tolF, L"z -= x [1]");
			Assert::AreEqual(0.0f, pDst->data.f[2], tolF, L"z -= x [2]");

			BLBlas_ZEqNegateXF(rangeDst, rangeSrc);
			Assert::AreEqual(-fSrc[0], pDst->data.f[0], tolF, L"z = -x [0]");
			Assert::AreEqual(-fSrc[1], pDst->data.f[1], tolF, L"z = -x [1]");
			Assert::AreEqual(-fSrc[2], pDst->data.f[2], tolF, L"z = -x [2]");
			Assert::AreEqual(-fSrc[3], pDst->data.f[3], tolF, L"z = -x [3]");

			BLBlas_ZEqReciprocalXF(rangeDst, rangeSrc);
			Assert::AreEqual(1.0f / fSrc[1], pDst->data.f[1], tolF, L"z = 1.0/x [1]");
			Assert::AreEqual(1.0f / fSrc[2], pDst->data.f[2], tolF, L"z = 1.0/x [2]");
			Assert::AreEqual(1.0f / fSrc[3], pDst->data.f[3], tolF, L"z = 1.0/x [3]");
			BLArray_Delete(&pDst);
		}

		/*!
		\brief test two dependent variable operation like swap(x,y);
		*/
		TEST_METHOD(UTBlas_2v_float)
		{
			float f0[] = { -1.0f, -2.0f, -3.0f };
			float f1[] = { 1.0f, 2.0f, 3.0f };
			BLRange range0 = BLRange_Init(f0, f0 + ARRAYSIZE(f0));
			BLRange range1 = BLRange_Init(f1, f1 + ARRAYSIZE(f1));
			int ierr = BLBlas_SwapF(range0, range1);
			Assert::AreEqual((int)0, ierr, L"BLBlas_Swap() normal return code");
			for (int i = 0; i < ARRAYSIZE(f0); i++)
			{
				Assert::AreEqual((float)(i + 1), f0[i], tolF, L"f0");
				Assert::AreEqual((float)(-(i + 1)), f1[i], tolF, L"f1");
			}
		}

		/*!
		\brief test inner product
		*/
		TEST_METHOD(UTBlas_innerproduct)
		{
			const float f0[] = { 1.0f, 2.0f, 3.0f };
			const float f1[] = { 3.0f, 2.0f, 1.0f };
			BLCRange range0 = BLRange_Init(f0, f0 + ARRAYSIZE(f0));
			BLCRange range1 = BLRange_Init(f1, f1 + ARRAYSIZE(f1));
			float fip = 1.0;
			BLPtr pip = { (char*)&fip };
			int ierr = BLBlas_ZEqXInnerProductYF(pip, range0, range1);
			Assert::AreEqual((int)0, ierr, L"BLBlas_ZEqInnerProductYF() normal return code");
			Assert::AreEqual(10.0f, fip, tolF, L"Inner product result");
			BLCRange range2 = BLRange_Init(f1, f1 + 2);
			ierr = BLBlas_ZEqXInnerProductYF(pip, range0, range2);
			Assert::AreEqual((int)ERANGE, ierr, L"BLBlas_ZEqInnerProductYF() error return code");
		}
	};

	const float BLBlas::tolF = 1.0e-5;
	const double BLBlas::tolD = 1.0e-10;
}