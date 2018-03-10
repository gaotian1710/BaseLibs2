#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
#define WSTR8 L"0123‚ ‚¢‚¤‚¦"
#define U8STR u8"0123‚ ‚¢‚¤‚¦"
#define WSTR32 (WSTR8 WSTR8 WSTR8 WSTR8)
#define WSTR64 (WSTR8 WSTR8 WSTR8 WSTR8 WSTR8 WSTR8 WSTR8 WSTR8)
#define U8STR64 (U8STR U8STR U8STR U8STR U8STR U8STR U8STR U8STR)

	TEST_CLASS(UT_BLStringBuilder)
	{
	public:

		TEST_METHOD(NewAppendAndDelete)
		{
			int ierr = 0;
			PBLBuffer p = BLStringBuilder_New(16);
			for (size_t i = 0; i < 4; i++)
			{
				ierr = BLStringBuilder_AppendW(&p, WSTR8);
				if (ierr) break;
			}
			Assert::AreEqual(0, ierr, L"error code of BLStringBuilder_AppendW()");
			PBLArray strResult = BLStringBuilder_GetW(p);
			Assert::AreEqual(WSTR32, strResult->data.wc);
			for (size_t i = 0; i < 4; i++)
			{
				ierr = BLStringBuilder_AppendA(&p, U8STR);
				if (ierr) break;
			}
			Assert::AreEqual(0, ierr, L"error code of BLStringBuilder_AppendA()");
			BLArray_Delete(&strResult);
			strResult = BLStringBuilder_GetW(p);
			Assert::AreEqual(WSTR64, strResult->data.wc, L"BLStringBuilder_GetW() after appending eight strings");

			BLArray_Delete(&strResult);
			strResult = BLStringBuilder_GetA(p);
			Assert::AreEqual(U8STR64, strResult->data.c, L"BLStringArray_GetA() after appending eight strings");
			BLBuffer_Delete(&p);
		}

	};
}