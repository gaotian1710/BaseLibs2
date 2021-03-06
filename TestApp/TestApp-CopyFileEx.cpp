#include "stdafx.h"

using namespace std;

DWORD CALLBACK progressRoutine(
	LARGE_INTEGER TotalFileSize,
	LARGE_INTEGER TotalBytesTransferred,
	LARGE_INTEGER StreamSize,
	LARGE_INTEGER StreamBytesTransferred,
	DWORD dwStreamNumber,
	DWORD dwCallbackReason,
	HANDLE hSourceFile,
	HANDLE hDestinationFile,
	LPVOID lpData
)
{
	SYSTEMTIME end;
	GetLocalTime(&end);
	uint64_t msecs = *(uint64_t*)&end - *(uint64_t*)lpData;
	cout << TotalBytesTransferred.QuadPart << "/" << TotalFileSize.QuadPart << " bytes copied in " << " " << msecs << "  ms ...." << endl;
	return PROGRESS_CONTINUE;
}

int _tmain(int argc, TCHAR** argv)
{
	if (argc<3)
	{
		_tprintf(_T("usage: copyfile source dest\n"));
		return -1;
	}

	BOOL b = FALSE;

	SYSTEMTIME begin;
	GetLocalTime(&begin);

	//fstream debug("debug.log", fstream::in | fstream::out | fstream::app );
	//debug.open("debug.log", ios::app);

	BOOL result = CopyFileEx(argv[1], argv[2], &progressRoutine, &begin, &b, COPY_FILE_FAIL_IF_EXISTS);

	cout << (result ? "success" : "failed") << endl;

	return 0;

}