// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define STR7WCHAR	L"0123456"
#define STR8WCHAR	STR7WCHAR L"7"
#define STR9WCHAR	STR8WCHAR L"8"

int main()
{
	size_t ccBufLen = 8;
	size_t ccResult = 0;
	wchar_t* wstr = (wchar_t*)malloc((ccBufLen + 1) * sizeof(wchar_t));
	int iResult = _snwprintf_s(wstr, ccBufLen + 1, ccBufLen, L"%ws", STR8WCHAR);
	printf("buffer length = 8, source length = 8, written length = %d\n", iResult);
	iResult = _snwprintf_s(wstr, ccBufLen + 1, ccBufLen, L"%ws", STR9WCHAR);
	printf("buffer length = 8, source length = 9, written length = %d\n", iResult);
	iResult = _snwprintf_s(wstr, ccBufLen + 1, ccBufLen, L"%ws", STR7WCHAR);
	printf("buffer length = 8, source length = 7, written length = %d\n", iResult);

	int a = ( _snwprintf_s(wstr, ccBufLen + 1, ccBufLen, L"%ws", STR7WCHAR), 100);

	return 0;
}

