#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(BLBlas)
	{
		static const int ccBuffer = 256;
		static wchar_t buffer[ccBuffer];
	public:
		
		TEST_METHOD(UT_1v0c_float)
		{
			PBLArray p = BLArray_New(4, BLType_f);

			BLArray_Delete(&p);
		}

	};


}