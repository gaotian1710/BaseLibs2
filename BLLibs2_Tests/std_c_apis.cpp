#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UT_std_c_apis)
	{
		static const int ccBuffer = 256;
		static wchar_t buffer[ccBuffer];
	public:
		
		TEST_METHOD(UT_swprintf)
		{
			const wchar_t* str0 = L"‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e";
		}

	};

	wchar_t UT_std_c_apis::buffer[UT_std_c_apis::ccBuffer];
}