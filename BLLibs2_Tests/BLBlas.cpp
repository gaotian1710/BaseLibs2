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

			BLArray_Delete(&pDst);
		}
	};

	const float BLBlas::tolF = 1.0e-5;
	const double BLBlas::tolD = 1.0e-10;
}