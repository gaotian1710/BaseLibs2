#include "stdafx.h"
#include "BLError.h"

const wchar_t * BLError_TypeLabel(BLErrorType t)
{
	static const wchar_t* labels[] = {
		L"BLErrorType_BL",
		L"BLErrorType_Errno",
		L"BLErrorType_Win",
		L"BLErrorType_HRESULT",
		L"BLErrorType_Other"
	};
	return labels[t];
}

BLError BLError_MakeBL(int errorNumber)
{
	BLError e;
	e.typedNumber.err = errorNumber;
	e.typedNumber.type = BLErrorType_BL;
	return e;
}

BLError BLError_MakeErrno(int errorNumber)
{
	BLError e;
	e.typedNumber.err = errorNumber;
	e.typedNumber.type = BLErrorType_Errno;
	return e;
}

BLError BLError_MakeWin(int errorNumber)
{
	BLError e;
	e.typedNumber.err = errorNumber;
	e.typedNumber.type = BLErrorType_Win;
	return e;
}

BLError BLError_MakeHRESULT(int errorNumber)
{
	BLError e;
	e.typedNumber.err = errorNumber;
	e.typedNumber.type = BLErrorType_HRESULT;
	return e;
}

BLError BLError_MakeOther(int errorNumber)
{
	BLError e;
	e.typedNumber.err = errorNumber;
	e.typedNumber.type = BLErrorType_Other;
	return e;
}
