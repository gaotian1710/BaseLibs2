#include "stdafx.h"
#include "CppUnitTest.h"
#include "MatrixVectorData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(BLBlasStructured)
	{
		PCBLBlasInterface blasF, blasD, blasFc, blasDc;
		float tolF;
		double tolD;

	public:
		TEST_METHOD_INITIALIZE(Init)
		{
			blasF = BLBlas_GetInterface(BLType_f);
			blasD = BLBlas_GetInterface(BLType_d);
			blasFc = BLBlas_GetInterface(BLType_fc);
			blasDc = BLBlas_GetInterface(BLType_dc);
			tolF = MatrixVectorData::tolF;
			tolD = MatrixVectorData::tolD;
		}

		TEST_METHOD(Blas_t)
		{
			BLTypes t = BLType_f;
			Assert::AreEqual((int)t, (int)blasF->t);

			t = BLType_d;
			Assert::AreEqual((int)t, (int)blasD->t);

			t = BLType_fc;
			Assert::AreEqual((int)t, (int)blasFc->t);

			t = BLType_dc;
			Assert::AreEqual((int)t, (int)blasDc->t);
		}

		TEST_METHOD(Blas_fillOnesF)
		{
			size_t cuData = 3;
			PBLArray data = BLArray_New(cuData, BLType_f);

			// normal end
			{
				BLRange range = BLRange_Init(data->data.c, data->end.c);
				int ierr = blasF->fillOnes(range);
				Assert::AreEqual(0, ierr, L"normal end return code");
				for (size_t i = 0; i < cuData; i++)
				{
					Assert::AreEqual(1.0f, data->data.f[i], tolF);
				}
			}

#if defined(_DEBUG)
			// type mismatch
			{
				BLRange range = BLRange_Init(data->data.i16, data->data.i16 + 3);
				int ierr = blasF->fillOnes(range);
				Assert::AreEqual((int)ERANGE, ierr, L"data type mismatch return code");
			}

			//// buffer overrun
			//{
			//	BLRange range = BLRange_Init(data->data.f, data->end.f + 1);
			//	int ierr = blasF->fillOnes(range);
			//	Assert::AreEqual((int)ERANGE, ierr, L"buffer overrun return code");
			//}
#endif

			BLArray_Delete(&data);
		}

		TEST_METHOD(Blas_fillZerosF)
		{
			size_t cuData = 3;
			PBLArray data = BLArray_New(cuData, BLType_f);

			// normal end
			{
				BLRange range = BLRange_Init(data->data.f, data->end.f);
				int ierr = blasF->fillZeros(range);
				Assert::AreEqual(0, ierr, L"normal end return code");
				for (size_t i = 0; i < cuData; i++)
				{
					Assert::AreEqual(0.0f, data->data.f[i], tolF, L"element comparison");
				}
			}

#if defined(_DEBUG)
			// type mismatch
			{
				BLRange range = BLRange_Init(data->data.c, data->data.i16 + 3);
				int ierr = blasF->fillZeros(range);
				Assert::AreEqual((int)ERANGE, ierr, L"data type mismatch return code");
			}
#endif

			BLArray_Delete(&data);
		}

		TEST_METHOD(Blas_fillMinusOnesF)
		{
			size_t cuData = 3;
			PBLArray data = BLArray_New(cuData, BLType_f);

			// normal end
			{
				BLRange range = BLRange_Init(data->data.f, data->end.f);
				int ierr = blasF->fillMinusOnes(range);
				Assert::AreEqual(0, ierr, L"normal end return code");
				for (size_t i = 0; i < cuData; i++)
				{
					Assert::AreEqual(-1.0f, data->data.f[i], tolF, L"element comparison");
				}
			}

#if defined(_DEBUG)
			// type mismatch
			{
				BLRange range = BLRange_Init(data->data.c, data->data.i16 + 3);
				int ierr = blasF->fillMinusOnes(range);
				Assert::AreEqual((int)ERANGE, ierr, L"data type mismatch return code");
			}
#endif

			BLArray_Delete(&data);
		}

		TEST_METHOD(Blas_zEqXF_)
		{
			const size_t cuData = 6;
			float copyData[cuData];
			BLRange rangeCopy = BLRange_Init(copyData, copyData + cuData);
			BLCRange rangeSrc = BLRange_Init(MatrixVectorData::a2x3F, MatrixVectorData::a2x3F + cuData);

			// normal end
			{
				int ierr = blasF->zEqX(rangeCopy, rangeSrc);
				Assert::AreEqual(0, ierr, L"normal end return code");
				for (size_t i = 0; i < cuData; i++)
				{
					Assert::AreEqual(
						MatrixVectorData::a2x3F[i],
						copyData[i],
						tolF, L"element-by-element comparison"
					);
				}
			}

#if defined(_DEBUG)
			// size mismatch
			{
				BLCRange rangeSrc2 = BLRange_Init(MatrixVectorData::a2x3F, MatrixVectorData::a2x3F + 5);
				int ierr = blasF->zEqX(rangeCopy, rangeSrc2);
				Assert::AreEqual((int)ERANGE, ierr, L"size mismatch return code");
			}

			// buffer overrun
			//{
			//	float *pf = (float*)malloc(sizeof(float) * 5);
			//	float* pf2 = pf;
			//	BLRange rangeCopy = BLRange_Init(pf, pf + cuData);
			//	int ierr = blasF->zEqX(rangeCopy, rangeSrc);
			//	Assert::AreEqual((int)ERANGE, ierr, L"buffer overrun return code");
			//	free((void*)pf);
			//}
#endif
		}
	};


}