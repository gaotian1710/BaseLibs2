#include "stdafx.h"
#include "BLError.h"
#include "BLTypes.h"
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
			iResult = 0;
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
			iResult = -1;
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
			iResult = 0;
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


PBLArray BLString_ModifyPath0(const wchar_t* wstr, unsigned int i)
{
	PBLArray p = NULL;
	if (i >= 100) return p;
	p = BLString_NewW(wstr, wcslen(wstr) + 4);
	_snwprintf_s(p->data.wc + wcslen(wstr), 4, 3, L"-%02d", i);
	return p;
}

PBLArray BLString_ModifyPath1(const wchar_t * wstr, unsigned int i)
{
	PBLArray p = NULL;
	if (i >= 100) return p;
	p = BLString_NewW(wstr, wcslen(wstr) + 4);
	wchar_t* extPos = (wchar_t*)(p->end.wc);
	do {
		--extPos;
		if (*extPos == L'.') break;
	} while (extPos != p->data.wc);
	if (extPos == p->data.wc)
	{
		BLArray_Delete(&p);
	}
	else
	{
		size_t bufferLen = 4 + wcslen(extPos);
		PBLArray extension = BLString_NewW(extPos, 0);
		extPos += _snwprintf_s(extPos, bufferLen, bufferLen - 1, L"-%02d%ws", i, extension->data.wc);
		BLArray_Delete(&extension);
	}
	return p;
}

uint16_t BLString_Hash16(PBLArray p)
{
	uint32_t h = 0;
	uint8_t* s = p->data.c;
	while (s != p->end.c)
	{
		h = h * 23131 + *s;
		++s;
	}
	return (uint16_t)(h & (uint32_t)0xffff);
}

uint16_t BLString_Hash16raw(const wchar_t * p)
{
	uint32_t h = 0;
	uint8_t* p0 = (uint8_t*)p;
	uint8_t* p1 = (uint8_t*)(p + wcslen(p));
	while (p0 != p1)
	{
		h = h * 23131 + *p0;
		++p0;
	}
	return (uint16_t)(h & (uint32_t)0xffff);
}

/*
count characters in a string.
\param wstr [in] wide character string to investigate.
\param wcToCount [in] character to count
\return number of the target character in the string
*/
size_t BLString_CountChar(const wchar_t* wstr, wchar_t wcToCount)
{
	size_t c = 0;
	const wchar_t *p = wstr;
	while (*p != L'\0')
	{
		if (*p++ == wcToCount)
		{
			++c;
		}
	}
	return c;
}

PBLArray BLString_CsvDoubleQuotedString(PCBLArray wstr)
{
	return BLString_CsvDoubleQuatedStringRaw(wstr->data.wc);
}

PBLArray BLString_CsvDoubleQuatedStringRaw(const wchar_t * wstr)
{
	const wchar_t dq = L'"';
	const wchar_t wcNull = L'\0';
	size_t ccNew = wcslen(wstr) + BLString_CountChar(wstr, dq) + 3;
	PBLArray newStr = BLArray_New(ccNew, BLType_wc);
	const wchar_t* psrc = wstr;
	wchar_t *pdst = newStr->data.wc;
	*pdst++ = dq;
	while (*psrc != wcNull)
	{
		if (*psrc == dq)
		{
			*pdst++ = dq;
		}
		*pdst++ = *psrc++;
	}
	*pdst++ = dq;
	*pdst = wcNull;
	return newStr;
}
