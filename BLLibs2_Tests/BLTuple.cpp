#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UT_BLTuplePrivate)
	{
	public:
		static const size_t ccBuffer = 256;
		static wchar_t buffer[ccBuffer];

		TEST_METHOD_INITIALIZE(InitTests)
		{
			memset(buffer, 0, ccBuffer * sizeof(wchar_t));
		}

		TEST_METHOD(BLTupleFormatter_c_buffer_overflow)
		{
			BLData1 data;
			data.c = 'A';
			int i = BLTupleFormatter_c(BLTupleColumnPosition_Begin, buffer, 2, &data);
			Assert::AreEqual(1, i, L"1 character, buffer length=2");
			i = BLTupleFormatter_c(BLTupleColumnPosition_OnlyOne, buffer, 2, &data);
			Assert::AreEqual(-1, i, L"1 character and new line, buffer length=2");
			i = BLTupleFormatter_c(BLTupleColumnPosition_OnlyOne, buffer, 4, &data);
			Assert::AreEqual(3, i, L"1 character and new line, buffer length=4");
			i = BLTupleFormatter_c(BLTupleColumnPosition_End, buffer, 4, &data);
			Assert::AreEqual(-1, i, L"',', 1 character, and new line, buffer length=4");
			i = BLTupleFormatter_c(BLTupleColumnPosition_End, buffer, 5, &data);
			Assert::AreEqual(4, i, L"',', 1 character and new line, buffer length=5");
			Assert::AreEqual(L",A\r\n", buffer, L"finished string in buffer");
		}

		TEST_METHOD(BLTupleFormatter_wc_buffer_Overflow)
		{
			BLData1 data;
			data.wc = L'A';
			// appending one wide character
			int i = BLTupleFormatter_wc(BLTupleColumnPosition_Begin, buffer, 2, &data);
			Assert::AreEqual(1, i, L"1 character, buffer length=2");
			// appending one wide character and a new line, totally three characters, and then overflow and fail
			i = BLTupleFormatter_wc(BLTupleColumnPosition_OnlyOne, buffer, 2, &data);
			Assert::AreEqual(-1, i, L"1 character and new line, buffer length=2");
			// appending one wide character and a new line, totally three characters successfully
			i = BLTupleFormatter_wc(BLTupleColumnPosition_OnlyOne, buffer, 4, &data);
			Assert::AreEqual(3, i, L"1 character and new line, buffer length=4");
			// appending a ',', one wide character, and a new line, totally four characcters, and then overflow and fail.
			i = BLTupleFormatter_wc(BLTupleColumnPosition_End, buffer, 4, &data);
			Assert::AreEqual(-1, i, L"',', 1 character, and new line, buffer length=4");
			// appending a ',', one wide character, and a new line, totally four characcters successfully
			i = BLTupleFormatter_wc(BLTupleColumnPosition_End, buffer, 5, &data);
			Assert::AreEqual(4, i, L"',', 1 character and new line, buffer length=5");
			Assert::AreEqual(L",A\r\n", buffer, L"finished string in buffer");
		}

		TEST_METHOD(BLTupleFormatter_i8_buffer_overflow)
		{

		}

		TEST_METHOD(BLTupleFormatter_i16_buffer_overflow)
		{

		}
	};

	wchar_t UT_BLTuplePrivate::buffer[UT_BLTuplePrivate::ccBuffer];
}