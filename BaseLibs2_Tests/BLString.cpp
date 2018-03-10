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
	};

	const char* UT_BLString::u8str = u8"abc123こんにちは你好";
	const wchar_t* UT_BLString::u16str = L"abc123こんにちは你好";

}