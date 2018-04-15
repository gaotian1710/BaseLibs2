#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

wchar_t buffer[1024];

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UTBLArray)
	{
	public:
		
		TEST_METHOD(UTBLArray_NewByteCountUnitCountDelete)
		{
			Logger::WriteMessage(L"UTBLArray_NewByteCountUnitCountDelete entered.");
			PBLArray p = BLArray_New(2, BLType_dc);
			_snwprintf_s(buffer, ARRAYSIZE(buffer), ARRAYSIZE(buffer) - 1,
				L"p = 0x%I64x, p->data.c = 0x%I64x, p->end.c = 0x%I64x", (uint64_t)p, (uint64_t)(p->data.c), (uint64_t)(p->end.c)); 
			Logger::WriteMessage(buffer);
			Assert::AreEqual((size_t)32, (size_t)BLArray_ByteCount(p), L"byte count");
			Assert::AreEqual((size_t)32, (size_t)BLArray_UnitCount(p, BLType_c), L"character count");
			Assert::AreEqual((size_t)2, (size_t)BLArray_UnitCount(p, BLType_dc), L"double number count");
			Assert::AreEqual((size_t)8, (size_t)BLArray_UnitCount(p, BLType_ui32), L"uint32_t number count");
			BLArray_Delete(&p);
			Assert::AreEqual((void*)NULL, (void*)p, L"pointer was cleared.");
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