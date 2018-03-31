#include "stdafx.h"
#include "BLTypes.h"
#include "BLError.h"
#include "BLArray.h"
#include "BLString.h"
#include "BLStringBuilder.h"

PBLBuffer BLStringBuilder_New(size_t ccLength)
{
	return BLBuffer_New(ccLength, BLType_wc);
}

int BLStringBuilder_AppendW(PBLBuffer * pp, const wchar_t * wstr)
{
	int err = 0;
	PBLBuffer p = *pp;
	do {
		// get the available length in *pp.
		size_t ccAvailable = p->arrayData.end.wc - p->putter.wc - 1;
		size_t ccRequired = wcslen(wstr);

		// if the available length is insufficient, resize the buffer.
		if (ccAvailable < ccRequired)
		{
			// allocate a new buffer with a sufficient length
			size_t ccCurrentSize = BLArray_UnitCount(&(p->arrayData), BLType_wc);
			size_t ccAlloc = ccCurrentSize + max(ccCurrentSize, ccRequired * 2);
			PBLBuffer pNew = BLBuffer_New(ccAlloc, BLType_wc);
			if (pNew == NULL)
			{
				err = ENOMEM;
				break;
			}
			// copy the contents of the existing buffer to the new buffer.
			wmemcpy_s(pNew->arrayData.data.wc, ccAlloc, p->arrayData.data.wc,
				BLArray_UnitCount(&(p->arrayData), BLType_wc));
			pNew->getter.wc = pNew->arrayData.data.wc + (p->getter.wc - p->arrayData.data.wc);
			pNew->putter.wc = pNew->arrayData.data.wc + (p->putter.wc - p->arrayData.data.wc);

			BLBuffer_Delete(pp); // delete the old buffer
			p = *pp = pNew; // copy the new buffer to the existing pointers.
		}

		// append the string
		wcscpy_s(p->putter.wc, p->arrayData.end.wc - p->putter.wc, wstr);
		p->putter.wc += wcslen(wstr);
	} while (false);
	return err;
}

int BLStringBuilder_AppendW2(PBLBuffer * pp, const wchar_t * wstr0, const wchar_t * wstr1)
{
	int ierr = 0;
	do {
		if (wcslen(wstr0) > wcslen(wstr1))
		{
			ierr = BLStringBuilder_AppendW(pp, wstr0);
			if (ierr) break;
			ierr = BLStringBuilder_AppendW(pp, wstr1);
		}
		else
		{
			ierr = BLStringBuilder_AppendW(pp, wstr1);
			if (ierr) break;
			ierr = BLStringBuilder_AppendW(pp, wstr0);
		}
	} while (false);
	return ierr;
}

int BLStringBuilder_AppendA(PBLBuffer * pp, const char * str)
{
	PBLArray _str = BLString_NewA(str, 0);
	PBLArray _wstr = BLString_mbc2wc(_str);
	int ierr = BLStringBuilder_AppendW(pp, _wstr->data.wc);
	BLArray_Delete(&_wstr);
	BLArray_Delete(&_str);
	return ierr;
}

PBLArray BLStringBuilder_GetW(PBLBuffer p)
{
	return BLString_NewW(p->arrayData.data.wc, 0);
}

PBLArray BLStringBuilder_GetA(PBLBuffer p)
{
	return BLString_wc2mbc(&(p->arrayData));
}


