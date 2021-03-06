// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define WORK_PATH	L"C:\\Users\\yoshi\\Documents\\SWPrj\\10General\\BaseLibs2\\x64\\Debug\\Work\\BLSfo\\"
#define SRC_PATH	WORK_PATH L"CopySrc0.dat"
#define LOCAL_PATH	L"C:\\Users\\Public\\Downloads\\"
#define REMOTE_PATH	L"\\\\DESKTOP-SN3PDQC\\Users\\yoshi\\Documents\\exposed\\"
#define DST_PATH	LOCAL_PATH L"MoveDst0.dat"

#define ERROR_BREAK(line,err,msg) \
if (err) { \
	wprintf(L"%d, 0x%08x, %ws\n", line, err, msg); break; \
}

#define FILE_TIMEOUT	1000

int wmain(int argc, const wchar_t* *argv)
{
	wprintf(L"%ws\n", SRC_PATH);
	wprintf(L"%ws\n", DST_PATH);
	DWORD err = BLSfo_MoveFile(SRC_PATH, DST_PATH, FALSE);
	return (int)err;
}