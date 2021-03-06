// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define WORK_PATH	L"C:\\Users\\yoshi\\Desktop\\Server2016\\"
#define SRC_PATH	WORK_PATH L"14393.0.161119-1705.RS1_REFRESH_SERVERHYPERCORE_OEM_X64FRE_EN-US.ISO"
#define DST_PATH	WORK_PATH L"dst.iso"

#define ERROR_BREAK(line,err,msg) \
if (err) { \
	wprintf(L"%d, 0x%08x, %ws\n", line, err, msg); break; \
}

#define FILE_TIMEOUT	1000

DWORD MyDeleteFile(LPCWSTR filePath)
{
	HANDLE h = INVALID_HANDLE_VALUE;
	DWORD err = ERROR_SUCCESS;
	wchar_t desc[] = L"deleting a file";
	do {
		h = CreateTransaction(
			NULL,
			0,
			TRANSACTION_DO_NOT_PROMOTE,
			0,
			0,
			FILE_TIMEOUT,
			desc
		);
		if (h == INVALID_HANDLE_VALUE)
		{
			err = GetLastError();
			ERROR_BREAK(__LINE__, err, L"CreateTransaction()");
		}

		if (!DeleteFileTransacted(filePath, h))
		{
			err = GetLastError();
			ERROR_BREAK(__LINE__, err, L"DeleteFileTransacted()");
		}

		if (!CloseHandle(h))
		{
			err = GetLastError();
			ERROR_BREAK(__LINE__, err, L"DeleteFileTransacted()");
		}
		else
		{
			h = INVALID_HANDLE_VALUE;
		}
	} while (false);

	if (err) // error handling
	{
		if (h != INVALID_HANDLE_VALUE)
		{
			CloseHandle(h);
		}
	}
	return err;
}

const LPCWSTR CopyFile2MsgLabels[] = {
	L"Not defined",
	L"CHUNK_STARTED",
	L"CHUNK_FINISHED",
	L"STREAM_STARTED",
	L"STREAM_FINISHED",
	L"POLL_CONTINUE",
	L"ERROR"
};

void ShowCopyFile2Message(const COPYFILE2_MESSAGE* pmsg)
{
	wprintf(L"CopyFile2 message\n\tmessage type = %ws\n", CopyFile2MsgLabels[pmsg->Type]);
}

COPYFILE2_MESSAGE_ACTION CALLBACK MyCopyCallback(
	const COPYFILE2_MESSAGE* pmsg, PVOID pvContext
) {
	COPYFILE2_MESSAGE_ACTION action = COPYFILE2_PROGRESS_CONTINUE;
	ShowCopyFile2Message(pmsg);
	if (pmsg->Type == COPYFILE2_CALLBACK_STREAM_FINISHED)
	{
		HANDLE *ph = (HANDLE*)pvContext;
		SetEvent(*ph);
		action = COPYFILE2_PROGRESS_QUIET;
	}
	return action;
}
DWORD MyCopyFile(LPCWSTR src, LPCWSTR dst)
{
	DWORD err = ERROR_SUCCESS;
	HANDLE h = NULL;
	BOOL bCancel = FALSE;
	COPYFILE2_EXTENDED_PARAMETERS cf2param = { 
		sizeof(COPYFILE2_EXTENDED_PARAMETERS),
		0,
		&bCancel, // cancel flag
		MyCopyCallback, // progress callback
		(PVOID)&h // progress context
	};
	do {
		h = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (h == NULL)
		{
			err = GetLastError();
			ERROR_BREAK(__LINE__, err, L"CreateEvent()");
		}

		HRESULT hr = CopyFile2(src, dst, &cf2param);
		wprintf(L"CopyFile2() returned 0x%08x\n", 0xffff & hr);

		DWORD waitResult = WaitForSingleObject(h, FILE_TIMEOUT);
		switch (waitResult)
		{
		case WAIT_OBJECT_0:
			wprintf(L"CopyFile2() operation complete");
			break;
		case WAIT_TIMEOUT:
			wprintf(L"CopyFile2() operation timeout");
			err = ERROR_TIMEOUT;
			break;
		default:
			wprintf(L"CopyFile2() something wrong");
			err = GetLastError();
			break;
		}
	} while (false);
	return err;
}

int main()
{
	DWORD err = ERROR_SUCCESS;
	do {
		if (PathFileExists(DST_PATH))
		{
			err = MyDeleteFile(DST_PATH);
			if (err) break;
		}

		err = MyCopyFile(SRC_PATH, DST_PATH);
	} while (false);
	return (int)err;
}

