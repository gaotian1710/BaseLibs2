#include "stdafx.h"
#include "BLArray.h"
#include "BLString.h"


PBLArray BLString_NewA(const char * str, size_t cbBufferLength)
{
	PBLArray p = BLArray_New(__max(strlen(str) + 1, cbBufferLength), BLType_c);
	strcpy_s(p->data.c, BLArray_ByteCount(p), str);
	return p;
}

PBLArray BLString_NewW(const wchar_t * wstr, size_t ccBufferLength)
{
	PBLArray p = BLArray_New(__max(wcslen(wstr) + 1, ccBufferLength), BLType_wc);
	wcscpy_s(p->data.wc, BLArray_UnitCount(p, BLType_wc), wstr);
	return p;
}

PBLArray BLString_mbc2wc(PBLArray str)
{
	mbstate_t state = { 0 };
	size_t ccAlloc = strlen(str->data.c) + 1;
	PBLArray p = (PBLArray)NULL;

	const char* src = str->data.c;
	char16_t dummyDst, *dst;
	size_t dstLen = 0;
	size_t maxBytes = (size_t)(str->end.c - str->data.c);
	int iResult = 0;
	while (0 != (iResult = (int)mbrtoc16(&dummyDst, src, maxBytes, &state)))
	{
		if (iResult == -1) // error
		{
			break;
		}
		else if (iResult == -2) // no wide character but valid
		{
			iResult == 0;
			break;
		}
		else if (iResult == -3) // a wide character must be occupied but no source character is consumed.
		{
			dstLen++;
		}
		else if (iResult <= (int)maxBytes)
		{
			src += iResult;
			maxBytes -= iResult;
			dstLen++;
		}
		else
		{
			iResult == -1;
			break;
		}
	}
	if (iResult == -1)
	{
		return p;
	}
	p = BLArray_New(dstLen + 1, BLType_wc);
	dst = (char16_t*)(p->data.wc);
	maxBytes = (size_t)(str->end.c - str->data.c);
	state._Byte = 0;
	state._State = 0;
	state._Wchar = 0;
	src = str->data.c;
	while (0 != (iResult = (int)mbrtoc16(dst, src, maxBytes, &state)))
	{
		if (iResult == -2) // no wide character but valid
		{
			iResult == 0;
			break;
		}
		else if (iResult == -3) // a wide character must be occupied but no source character is consumed.
		{
			dst++;
		}
		else if (iResult <= (int)maxBytes)
		{
			src += iResult;
			maxBytes -= iResult;
			dst++;
		}
		if (dst == (char16_t*)(p->end.wc))
		{
			break;
		}
		continue;
	}
	return p;
}

PBLArray BLString_wc2mbc(PBLArray wstr)
{
	mbstate_t state = { 0 };
	PBLArray p = NULL;
	size_t cbDst = 0; // byte size of result string
	const char16_t* src = (const char16_t*)(wstr->data.c);
	char dummyDst[4] = { 0 };
	int result = 0;
	while (*src != L'\0' && src != wstr->end.wc)
	{
		result = (int)c16rtomb(dummyDst, *src, &state);
		if (result == -1) // err
		{
			break;
		}
		else
		{
			cbDst += result;
			src++;
		}
	}
	if (result == -1) return p;
	state._Byte = 0;
	state._State = 0;
	state._Wchar = 0;
	p = BLArray_New(cbDst + 1, BLType_c);
	src = (const char16_t*)(wstr->data.c);
	char* dst = p->data.c;
	while (*src != L'\0'  && src != wstr->end.wc)
	{
		result = (int)c16rtomb(dst, *src, &state);
		if (result == -1) // err
		{
			break;
		}
		else
		{
			dst += result;
			src++;
		}
	}
	return p;
}