#include "stdafx.h"
#define _BLTypes_c
#include "BLTypes.h"

const wchar_t* const BLTypeLabels[] = {
	L"BLType_c",
	L"BLType_wc",
	L"BLType_i8",
	L"BLType_i16",
	L"BLType_i32",
	L"BLType_i64",
	L"BLType_ui8",
	L"BLType_ui16",
	L"BLType_ui32",
	L"BLType_ui64",
	L"BLType_f",
	L"BLType_d",
	L"BLType_fc",
	L"BLType_dc",
	L"BLType_ptr",
	L"BLType_type",
	L"BLType_ccstr",
	L"BLType_cwcstr",
	L"BLType_cstr",
	L"BLType_wcstr"
};

#pragma region BLNorm definitions
float BLNorm_c(BLCPtr p)
{
	return (float)abs((int)(*p.c));
}

float BLNorm_wc(BLCPtr p)
{
	return (float)abs((int)(*p.wc));
}

float BLNorm_i8(BLCPtr p)
{
	return (float)abs((int)(*p.i8));
}

float BLNorm_i16(BLCPtr p)
{
	return (float)abs((int)(*p.i16));
}

float BLNorm_i32(BLCPtr p)
{
	return (float)abs((int)(*p.i32));
}

float BLNorm_i64(BLCPtr p)
{
	return (float)abs((int)(*p.i64));
}

float BLNorm_ui8(BLCPtr p)
{
	return (float)(*p.ui8);
}

float BLNorm_ui16(BLCPtr p)
{
	return (float)(*p.ui16);
}

float BLNorm_ui32(BLCPtr p)
{
	return (float)(*p.ui32);
}

float BLNorm_ui64(BLCPtr p)
{
	return (float)(*p.ui64);
}

float BLNorm_f(BLCPtr p)
{
	return fabsf(*p.f);
}

float BLNorm_d(BLCPtr p)
{
	return (float)fabs(*p.d);
}

float BLNorm_fc(BLCPtr p)
{
	return normf(*p.fc);
}

float BLNorm_dc(BLCPtr p)
{
	return (float)norm(*p.dc);
}

const BLNorm BLNormFunctions[] = {
	BLNorm_c, BLNorm_wc,
	BLNorm_i8, BLNorm_i16, BLNorm_i32, BLNorm_i64,
	BLNorm_ui8, BLNorm_ui16, BLNorm_ui32, BLNorm_ui64,
	BLNorm_f, BLNorm_d, BLNorm_fc, BLNorm_dc
};
#pragma endregion BLNorm definitions

#pragma region BLCopyS definitions
void BLCopyS_c(BLPtr dst, BLCPtr src)
{
	*dst.c = *src.c;
}
void BLCopyS_wc(BLPtr dst, BLCPtr src)
{
	*dst.wc = *src.wc;
}
void BLCopyS_i8(BLPtr dst, BLCPtr src)
{
	*dst.i8 = *src.i8;
}
void BLCopyS_i16(BLPtr dst, BLCPtr src)
{
	*dst.i16 = *src.i16;
}
void BLCopyS_i32(BLPtr dst, BLCPtr src)
{
	*dst.i32 = *src.i32;
}
void BLCopyS_i64(BLPtr dst, BLCPtr src)
{
	*dst.i64 = *src.i64;
}
void BLCopyS_ui8(BLPtr dst, BLCPtr src)
{
	*dst.ui8 = *src.ui8;
}
void BLCopyS_ui16(BLPtr dst, BLCPtr src)
{
	*dst.ui16 = *src.ui16;
}
void BLCopyS_ui32(BLPtr dst, BLCPtr src)
{
	*dst.ui32 = *src.ui32;
}
void BLCopyS_ui64(BLPtr dst, BLCPtr src)
{
	*dst.ui64 = *src.ui64;
}
void BLCopyS_f(BLPtr dst, BLCPtr src)
{
	*dst.f = *src.f;
}
void BLCopyS_d(BLPtr dst, BLCPtr src)
{
	*dst.d = *src.d;
}
void BLCopyS_fc(BLPtr dst, BLCPtr src)
{
	*dst.fc = *src.fc;
}
void BLCopyS_dc(BLPtr dst, BLCPtr src)
{
	*dst.dc = *src.dc;
}

const BLCopyS BLCopySFunctions[] =
{
	BLCopyS_c, BLCopyS_wc,
	BLCopyS_i8, BLCopyS_i16, BLCopyS_i32, BLCopyS_i64,
	BLCopyS_ui8, BLCopyS_ui16, BLCopyS_ui32, BLCopyS_ui64,
	BLCopyS_f, BLCopyS_d, BLCopyS_fc, BLCopyS_dc
};
#pragma endregion BLCopyS definitions

#pragma region BLReciprocalS definitions
void BLReciprocalS_c(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_wc(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_i8(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_i16(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_i32(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_i64(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_ui8(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_ui16(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_ui32(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_ui64(BLPtr dst, BLCPtr src)
{
	abort();
}
void BLReciprocalS_f(BLPtr dst, BLCPtr src)
{
	*dst.f = 1.0f / *src.f;
}
void BLReciprocalS_d(BLPtr dst, BLCPtr src)
{
	*dst.d = 1.0 / *src.d;
}
void BLReciprocalS_fc(BLPtr dst, BLCPtr src)
{
	float normSrc = normf(*src.fc);
	*dst.fc = _FCOMPLEX_(crealf(*src.fc) / normSrc, -cimagf(*src.fc) / normSrc);
}
void BLReciprocalS_dc(BLPtr dst, BLCPtr src)
{
	double normSrc = norm(*src.dc);
	*dst.dc = _DCOMPLEX_(creal(*src.dc) / normSrc, -cimag(*src.dc) / normSrc);
}

const BLCopyS BLReciprocalSFunctions[] =
{
	BLReciprocalS_c, BLReciprocalS_wc,
	BLReciprocalS_i8, BLReciprocalS_i16, BLReciprocalS_i32, BLReciprocalS_i64,
	BLReciprocalS_ui8, BLReciprocalS_ui16, BLReciprocalS_ui32, BLReciprocalS_ui64,
	BLReciprocalS_f, BLReciprocalS_d, BLReciprocalS_fc, BLReciprocalS_dc
};
#pragma endregion BLReciprocalS definitions
