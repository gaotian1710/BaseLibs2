#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UTBLArray)
	{
	public:
		
		TEST_METHOD(UTBLArray_NewByteCountUnitCountDelete)
		{
			PBLArray p = BLArray_New(2, BLType_dc);
			Assert::AreEqual((size_t)32, BLArray_ByteCount(p));
			Assert::AreEqual((size_t)32, BLArray_UnitCount(p, BLType_c));
			Assert::AreEqual((size_t)2, BLArray_UnitCount(p, BLType_dc));
			Assert::AreEqual((size_t)8, BLArray_UnitCount(p, BLType_ui32));
			BLArray_Delete(&p);
			Assert::AreEqual((void*)NULL, (void*)p);
		}

		TEST_METHOD(UTBLArray_PutI8GetI32)
		{
			PBLArray p = BLArray_New(1, BLType_i32);
			size_t cuI8 = BLArray_UnitCount(p, BLType_i8);
			for (size_t i = 0u; i < cuI8; i++)
			{
				p->data.i8[i] = (int8_t)(i + 10u);
			}
			const int32_t refValue =
				10 + 11 * 0x100 + 12 * 0x10000 + 13 * 0x1000000;
			Assert::AreEqual(refValue, p->data.i32[0]);
			BLArray_Delete(&p);
		}

		TEST_METHOD(UTBLArray_EndPtr)
		{
			size_t unitCount = 1;
			PBLArray p = BLArray_New(unitCount, BLType_dc);
			ptrdiff_t diff = (p->data.i8 + unitCount * BLUnitSizes[BLType_dc]) - (p->end.i8);
			Assert::AreEqual((int)0, (int)diff);
			BLArray_Delete(&p);
		}
	};
}