#include "stdafx.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	TEST_CLASS(UT_BLSfo)
	{
		static wchar_t TestDataPath[MAX_PATH];
	public:
		TEST_CLASS_INITIALIZE(InitClass)
		{
			wchar_t WorkPath[MAX_PATH];
			GetCurrentDirectory(sizeof(WorkPath), WorkPath);
			PathAppend(WorkPath, L"Work\\BLSfo");
			wcscpy_s(TestDataPath, MAX_PATH, WorkPath);
		}

		TEST_METHOD(Delete_Normal)
		{
			wchar_t workPath[MAX_PATH];
			wcscpy_s(workPath, MAX_PATH, TestDataPath);
			PathAppend(workPath, L"DeleteTarget0.dat");
			if (!PathFileExists(workPath))
			{
				Assert::Fail(L"Delete target file does not exists at $(OutDir)Work\\BLFso\\DeleteTarget0.dat");
			}
			DWORD err = BLSfo_DeleteFile(workPath);
			Assert::AreEqual((DWORD)ERROR_SUCCESS, err, L"BLSfo_DeleteFile(valid-path) return code");
			Assert::AreEqual((BOOL)FALSE, PathFileExists(workPath), L"file existence just after BLSfo_DeleteFile()");
		}

		/*!
		\brief delete not existing file and fail
		*/
		TEST_METHOD(Delete_Fail)
		{
			wchar_t workPath[MAX_PATH];
			wcscpy_s(workPath, MAX_PATH, TestDataPath);
			PathAppend(workPath, L"DeleteTarget1.dat");
			if (!PathFileExists(workPath))
			{
				Assert::Fail(L"Delete target file does not exist at $(OutDir)work\\BLFso\\DeleteTarget1.dat");
			}
			DWORD err = BLSfo_DeleteFile(workPath);
			Assert::AreEqual((DWORD)ERROR_ACCESS_DENIED, err, L"BLSfo_DeleteFile(readonly-path) return code");
			Assert::AreEqual((BOOL)TRUE, PathFileExists(workPath), L"file existence just after BLSfo_DeleteFile()");
		}

		/*!
		\brief copy normally
		*/
		TEST_METHOD(Copy_Normal)
		{
			wchar_t workPath[MAX_PATH];
			wcscpy_s(workPath, MAX_PATH, TestDataPath);
			PathAppend(workPath, L"CopySrc0.dat");
			if (!PathFileExists(workPath))
			{
				Assert::Fail(L"Copy source file does not exist at $(OutDir)work\\BLFso\\CopySrc0.dat");
			}
			wchar_t* src0 = wcsdup(workPath);
			*(PathFindFileName(workPath)) = L'\0';
			PathAppend(workPath, L"CopyDst0.dat");
			if (PathFileExists(workPath))
			{
				Assert::Fail(L"Copy destination file exists at $(OutDir)work\\BLSfo\\CopyDst0.dat");
			}
			DWORD err = BLSfo_CopyFile(src0, workPath, FALSE);
			Assert::AreEqual((DWORD)ERROR_SUCCESS, err, L"BLSfo_CopyFile() success return code");
			if (!PathFileExists(workPath))
			{
				Assert::Fail(L"Copy destination file does not exist after calling BLSfo_CopyFile()");
			}
			err = BLSfo_CopyFile(src0, workPath, FALSE);
			Assert::AreEqual((DWORD)ERROR_FILE_EXISTS, err, L"BLSfo_CopyFile() return code copying to existing location without force");
			err = BLSfo_CopyFile(src0, workPath, TRUE);
			Assert::AreEqual((DWORD)ERROR_SUCCESS, err, L"error code force copy");
			free((void*)src0);
		}

		/*!
		\brief move file normally
		*/
		TEST_METHOD(Move_Normal)
		{
			wchar_t workPath[MAX_PATH];
			wcscpy_s(workPath, MAX_PATH, TestDataPath);
			PathAppend(workPath, L"CopySrc0.dat");
			if (!PathFileExists(workPath))
			{
				Assert::Fail(L"Copy source file does not exist at $(OutDir)work\\BLFso\\CopySrc0.dat");
			}
			wchar_t* src0 = wcsdup(workPath);
			*(PathFindFileName(workPath)) = L'\0';
			PathAppend(workPath, L"MoveDst0.dat");
			Assert::AreEqual(FALSE, PathFileExists(workPath),
				L"Move destination file exists at $(OutDir)work\\BLSfo\\CopyDst0.dat before move operation.");
			DWORD err = BLSfo_MoveFile(src0, workPath, FALSE);
			Assert::AreEqual((DWORD)ERROR_SUCCESS, err, L"BLSfo_MoveFile() success return code");
			Assert::AreEqual(TRUE, PathFileExists(workPath),
				L"Move destination file does not exist after calling BLSfo_MoveFile()");
			Assert::AreEqual(FALSE, PathFileExists(src0), 
				L"Move source file exists after move operation.");

			free((void*)src0);
		}
	};

	wchar_t UT_BLSfo::TestDataPath[MAX_PATH];
}