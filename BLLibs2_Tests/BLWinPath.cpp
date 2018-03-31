#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UT_BLWinPath)
	{
	public:
		/*
		Get module path of this unit test project
		*/
		TEST_METHOD(GetModulePathOfThisDLL)
		{
			const wchar_t* names[] = {
				L"BaseLibs2_Tests.dll",
				NULL
			};

			PBLArray p = BLWinPath_GetModulePath(names);
			Assert::AreNotEqual((void*)NULL, (void*)p);
			Assert::AreEqual(0, _wcsnicmp(L"C:\\", p->data.wc, 3), L"check disk drive letter");
			Assert::AreEqual(0, _wcsicmp(L"BaseLibs2_Tests.dll", PathFindFileName(p->data.wc)), L"check base filename");
		}

	};
}