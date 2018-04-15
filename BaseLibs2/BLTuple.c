#include "stdafx.h"
#include "BLError.h"
#include "BLTypes.h"
#include "BLArray.h"
#include "BLTuple.h"
#include "BLString.h"

PBLTuple BLTuple_New(size_t cElements)
{
	size_t cbTuple = cElements * sizeof(BLVariant);
	size_t cbAlloc = sizeof(BLTuple) + cbTuple;
	PBLTuple p = (PBLTuple)malloc(cbAlloc);
	if (p) p->end = (PCBLVariant)(p + 1);
	return p;
}

void BLTuple_Delete(PBLTuple * pp)
{
	if (pp && *pp)
	{
		free(*pp);
		*pp = NULL;
	}
}

size_t BLTuple_Count(PCBLTuple p)
{
	return p->end - p->tuple;
}


#pragma region default formatters
int BLTupleFormatter_c(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%c\r\n", L"%c", L",%c", L",%c\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->c[0]);
}

int BLTupleFormatter_wc(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%wc\r\n", L"%wc", L",%wc", L",%wc\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->wc[0]);
}

int BLTupleFormatter_i8(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%d\r\n", L"%d", L",%d", L",%d\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->i8[0]);
}

int BLTupleFormatter_i16(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%d\r\n", L"%d", L",%d", L",%d\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->i16[0]);
}

int BLTupleFormatter_i32(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%d\r\n", L"%d", L",%d", L",%d\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->i32[0]);
}

int BLTupleFormatter_i64(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%d\r\n", L"%d", L",%d", L",%d\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->i64[0]);
}

int BLTupleFormatter_ui8(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%u\r\n", L"%u", L",%u", L",%u\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->ui8[0]);
}

int BLTupleFormatter_ui16(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%u\r\n", L"%u", L",%u", L",%u\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->ui16[0]);
}

int BLTupleFormatter_ui32(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%u\r\n", L"%u", L",%u", L",%u\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->ui32[0]);
}

	
int BLTupleFormatter_ui64(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%u\r\n", L"%u", L",%u", L",%u\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->ui64[0]);
}
int BLTupleFormatter_f(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%e\r\n", L"%e", L",%e", L",%e\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->f[0]);
}
int BLTupleFormatter_d(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%e\r\n", L"%e", L",%e", L",%e\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->d[0]);
}

int BLTupleFormatter_fc(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%e + j%e\r\n", L"%e + j%e", L",%e + j%e", L",%e + j%e\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], crealf(data->fc[0]), cimagf(data->fc[0]));
}

int BLTupleFormatter_dc(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%e + j%e\r\n", L"%e + j%e", L",%e + j%e", L",%e + j%e\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], creal(data->dc[0]), cimag(data->dc[0]));
}

int BLTupleFormatter_ptr(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"0x%016x\r\n", L"0x%016x", L",0x%016x", L",0x%016x\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], data->ptr[0]);
}

int BLTupleFormatter_type(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%ws\r\n", L"%ws", L",%ws", L",%ws\r\n"
	};
	return _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], BLTypeLabels[data->type[0]]);
}
	
int BLTupleFormatter_ccstr(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%hs\r\n", L"%hs", L",%hs", L",%hs\r\n"
	};
	PBLArray cstr = BLString_NewA(data->ccstr[0], 0);
	PBLArray wcstr = BLString_mbc2wc(cstr);
	BLArray_Delete(&cstr);
	PBLArray dqedwcstr = BLString_CsvDoubleQuotedString(wcstr);
	BLArray_Delete(&wcstr);
	int i = _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], dqedwcstr->data.wc[0]
	);
	BLArray_Delete(&dqedwcstr);
	return i;
}

int BLTupleFormatter_cwcstr(
	BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data)
{
	const wchar_t* formatStrings[] = {
		L"%ws\r\n", L"%ws", L",%ws", L",%ws\r\n"
	};
	PBLArray dqedString = BLString_CsvDoubleQuatedStringRaw(data->cwcstr[0]);

	int i = _snwprintf_s(
		buffer, bufferLength, bufferLength - 1, formatStrings[pos], dqedString->data.wc[0]
	);
	BLArray_Delete(&dqedString);
	return i;
}


const BLTupleFormatter BLTuple_DefaultFormatters[] = {
	BLTupleFormatter_c,
	BLTupleFormatter_wc,
	BLTupleFormatter_i8,
	BLTupleFormatter_i16,
	BLTupleFormatter_i32,
	BLTupleFormatter_i64,
	BLTupleFormatter_ui8,
	BLTupleFormatter_ui16,
	BLTupleFormatter_ui32,
	BLTupleFormatter_ui64,
	BLTupleFormatter_f,
	BLTupleFormatter_d,
	BLTupleFormatter_fc,
	BLTupleFormatter_dc,
	BLTupleFormatter_ptr,
	BLTupleFormatter_type,
	BLTupleFormatter_ccstr,
	BLTupleFormatter_cwcstr,
	BLTupleFormatter_ccstr,
	BLTupleFormatter_cwcstr
};

// implementations

#pragma endregion default formatters

/*
try to format tuple into work.
return -1 if it fails to format due to shortage of buffer in work.
*/
int BLTuple_PreFormat(PBLArray work, PCBLTuple tuple, const BLTupleFormatter* formatters)
{
	int i = -1;
	int available = (int)BLArray_UnitCount(work, BLType_wc);
	wchar_t* wrptr = work->data.wc;
	PCBLVariant element = tuple->tuple;
	PCBLVariant last = tuple->end - 1;
	BLTupleColumnPosition pos = BLTuple_Count(tuple) == 1 ?
		BLTupleColumnPosition_OnlyOne : BLTupleColumnPosition_Begin;
	while (element != tuple->end)
	{
		i = formatters[element->type](pos, wrptr, available, &element->data);
		if (i < 0) break;
		wrptr += i;
		available -= i;
		pos = (++element == last) ? BLTupleColumnPosition_End : BLTupleColumnPosition_Other;
	}
	return i;
}

int BLTuple_Format(PBLArray * ppBuffer, PCBLTuple tuple, const BLTupleFormatter* formatters)
{
	size_t ccNew = BLTuple_Count(tuple) * 16;
	int i = -1;
	PBLArray work = NULL;
	do {
		do { // try to preformat until success.
			work = BLArray_New(ccNew, BLType_wc);
			if (work == NULL) break; // error
			i = BLTuple_PreFormat(work, tuple, formatters);
			if (i < 0)
			{
				BLArray_Delete(&work);
				ccNew *= 2;
			}
		} while (i < 0);
		if (i < 0) break; // error

		// if *ppBuffer has not been initialized or has insufficient size,
		// it is initialized with a sufficient size.
		if ((*ppBuffer) == NULL ||
			(BLArray_UnitCount(*ppBuffer, BLType_wc) < (wcslen(work->data.wc) + 1)))
		{ 	// *ppBuffer has insufficient size
			BLArray_Delete(ppBuffer);
			*ppBuffer = BLString_NewW(work->data.wc, 0);
		}
		wcscpy_s((*ppBuffer)->data.wc, BLArray_UnitCount(*ppBuffer, BLType_wc),
			work->data.wc);
		i = (int)wcslen((*ppBuffer)->data.wc);
	} while (false);
	BLArray_Delete(&work);
	return i;
}
