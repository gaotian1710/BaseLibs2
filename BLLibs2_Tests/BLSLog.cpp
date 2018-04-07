#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UT_BLSLog)
	{
	public:
		static const wchar_t* logFilePath;

		void BLSLog_WriteLogs()
		{
			BLSLog_Debug(L"%ws", L"これは debug log.");
			BLSLog_Info(L"%ws", L"这是info log.");
			BLSLog_Error(L"%ws", L"This is an error log.");
		}

		TEST_METHOD(BLSLog_OpenWriteClose_NewFile)
		{
			if (PathFileExists(logFilePath))
			{
				DeleteFile(logFilePath);
			}

			BLError err = BLSLog_Open(logFilePath, BLSLogLevel_Error);
			Assert::AreEqual(0, (int)err.typedNumber.err, L"return code of BLSLog_Open()");
			BLSLog_WriteLogs();
			err = BLSLog_Close();
			Assert::AreEqual(0, (int)err.typedNumber.err, L"return code of BLSLog_Close()");

			err = BLSLog_Open(logFilePath, BLSLogLevel_Info);
			Assert::AreEqual(0, (int)err.typedNumber.err, L"return code of BLSLog_Open()");
			BLSLog_WriteLogs();
			err = BLSLog_Close();
			Assert::AreEqual(0, (int)err.typedNumber.err, L"return code of BLSLog_Close()");

			err = BLSLog_Open(logFilePath, BLSLogLevel_Debug);
			Assert::AreEqual(0, (int)err.typedNumber.err, L"return code of BLSLog_Open()");
			BLSLog_WriteLogs();
			err = BLSLog_Close();
			Assert::AreEqual(0, (int)err.typedNumber.err, L"return code of BLSLog_Close()");
		}

	};

	const wchar_t* UT_BLSLog::logFilePath = L"BLSLog.log";
}