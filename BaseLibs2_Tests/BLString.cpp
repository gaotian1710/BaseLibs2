#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UT_BLString)
	{
	public:
		static const char* u8str;
		static const wchar_t* u16str;
		static const wchar_t* testPath;
		static const wchar_t* testPathMod0;
		static const wchar_t* testPathMod1;

		TEST_METHOD_INITIALIZE(InitTests)
		{
			setlocale(LC_ALL, "en_US.UTF-8");
		}

		TEST_METHOD(UTBLString_NewA)
		{
			PBLArray p = BLString_NewA(u8str, _mbstrlen(u8str));
			Assert::AreEqual(u8str, p->data.c);
			BLArray_Delete(&p);
		}

		TEST_METHOD(UTBLString_NewW)
		{
			PBLArray p = BLString_NewW(u16str, wcslen(u16str) + 1);
			Assert::AreEqual(u16str, p->data.wc);
			BLArray_Delete(&p);
		}

		TEST_METHOD(UTBLSring_mbc2wc)
		{
			PBLArray p = BLString_NewA(u8str, _mbstrlen(u8str));
			PBLArray p2 = BLString_mbc2wc(p);
			Assert::AreNotEqual((const void*)NULL, (const void*)p2);
			Assert::AreEqual(p2->data.wc, u16str);
		}

		TEST_METHOD(UTBLString_wc2mbc)
		{
			PBLArray p = BLString_NewW(u16str, wcslen(u16str) + 1);
			PBLArray p2 = BLString_wc2mbc(p);
			Assert::AreEqual(p2->data.c, u8str);
		}

		TEST_METHOD(UTBLString_ModifyPath0)
		{
			PBLArray modified = BLString_ModifyPath0(testPath, 15);
			Assert::AreEqual(testPathMod0, modified->data.wc);
		}

		TEST_METHOD(UTBLString_ModfyPath1)
		{
			PBLArray modified = BLString_ModifyPath1(testPath, 99);
			Assert::AreEqual(testPathMod1, modified->data.wc);
		}

		TEST_METHOD(UTBLSring_CsvDoubleQuotedString)
		{
			PBLArray psrc = BLString_NewW(L"abc\"def\"ghi", 0);
			LPCWSTR refStr = L"\"abc\"\"def\"\"ghi\"";
			PBLArray dqed = BLString_CsvDoubleQuotedString(psrc);
			Assert::AreEqual(refStr, dqed->data.wc, L"double quoted string");
			Assert::AreEqual(wcslen(refStr), (size_t)(dqed->end.wc - dqed->data.wc - 1),
				L"string length and buffer size");
		}
	};

	const char* UT_BLString::u8str = u8"abc123こんにちは你好";
	const wchar_t* UT_BLString::u16str = L"abc123こんにちは你好";
	const wchar_t* UT_BLString::testPath = L"C:\\Windows\\System32\\cmd.exe";
	const wchar_t* UT_BLString::testPathMod0 = L"C:\\Windows\\System32\\cmd.exe-15";
	const wchar_t* UT_BLString::testPathMod1 = L"C:\\Windows\\System32\\cmd-99.exe";
}