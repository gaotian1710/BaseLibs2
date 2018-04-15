#include "stdafx.h"
#include "BLTypes.h"
#include "BLError.h"
#include "BLArray.h"
#include "BLBlas.h"

#pragma region float operations
#pragma region _1v0c operations

int BLBlas_ZEqZeroF(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = 0.0f;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqOneF(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = 1.0f;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqMinusOneF(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = -1.0f;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion _1v0c operations

#pragma region _1v1c operations
int BLBlas_ZEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZAddEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) += *(x.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZSubEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) -= *(x.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZMulEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) *= *(x.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZDivEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) /= *(x.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqNegateXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = (-1.0f) * (*(x.scan.f++));
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqReciprocalXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = 1.0f / (*(x.scan.f++));
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZMulEqXsF(BLRange z, BLCPtr x)
{
	BLRange_Check1DBG(&z, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) *= *x.f;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion _1v1c operations
#pragma region _2v operations
int BLBlas_SwapF(BLRange x, BLRange y)
{
	BLRange_Check2VDBG(&x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		float f = *(x.scan.f);
		*(x.scan.f++) = *(y.scan.f);
		*(y.scan.f++) = f;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion _2v operations
#pragma region _1v2c operations
int BLBlas_ZEqXAddYF(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++) + *(y.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZEqXSubYF(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++) - *(y.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZEqXMulYF(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++) * *(y.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZEqXDivYF(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++) / *(y.scan.f++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZAddEqXMulYsF(BLRange z, BLCRange x, BLCPtr ys)
{
	BLRange_Check2DBG(&z, &x, BLType_f);
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) += (*(x.scan.f++)) * (*ys.f);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXInnerProductYF(BLPtr z, BLCRange x, BLCRange y)
{
	BLRange_Check2CDBG(&x, &y, BLType_f);
	*z.f = 0.0f;
	while (x.scan.f != x.end.f)
	{
		*z.f += (*(x.scan.f++)) * (*(y.scan.f++));
	}
	BLBlas_Return(__FILE__, __LINE__);
}

void BLBlas_ZsEqXsF(BLPtr zs, BLCPtr xs)
{
	*zs.f = *xs.f;
}

void BLBlas_ZsEqNegateXsF(BLPtr zs, BLCPtr xs)
{
	*zs.f = -(*xs.f);
}

void BLBlas_ZsEqReciprocalXsF(BLPtr zs, BLCPtr xs)
{
	*zs.f = 1.0f / *xs.f;
}

void BLBlas_ZsEqZeroF(BLPtr zs)
{
	*zs.f = 0.0f;
}

void BLBlas_ZsEqOneF(BLPtr zs)
{
	*zs.f = 1.0f;
}

float BLBlas_NormF(BLCPtr xs)
{
	return (*xs.f) * (*xs.f);
}

#pragma endregion _1v2c operations
#pragma endregion float operations

#pragma region double operations
int BLBlas_ZEqZeroD(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_d);
	while (z.scan.d != z.end.d)
	{
		*z.scan.d++ = 0.0;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqOneD(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_d);
	while (z.scan.d != z.end.d)
	{
		*z.scan.d++ = 1.0;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqMinusOneD(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_d);
	while (z.scan.d != z.end.d)
	{
		*z.scan.d++ = -1.0;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXD(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) = *(x.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZAddEqXD(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) += *(x.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZSubEqXD(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) -= *(x.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZMulEqXD(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) *= *(x.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZDivEqXD(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) /= *(x.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqNegateXD(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) = -(*(x.scan.d++));
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqReciprocalXD(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) = 1.0 / (*(x.scan.d++));
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZMulEqXsD(BLRange z, BLCPtr x)
{
	BLRange_Check1DBG(&z, BLType_d); // range check is effective only when _DEBUG is defined.
	while (z.scan.d != z.end.d)
	{
		*(z.scan.d++) *= *x.d;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_SwapD(BLRange x, BLRange y)
{
	BLRange_Check2VDBG(&x, &y, BLType_d); // range check is effective only when _DEBUG is defined.
	while (x.scan.d != x.end.d)
	{
		double d = *(x.scan.d);
		*(x.scan.d++) = *(y.scan.d);
		*(y.scan.d++) = d;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXAddYD(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_d); // range check is effective only when _DEBUG is defined.
	while (x.scan.d != x.end.d)
	{
		*(z.scan.d++) = *(x.scan.d++) + *(y.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXSubYD(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_d); // range check is effective only when _DEBUG is defined.
	while (x.scan.d != x.end.d)
	{
		*(z.scan.d++) = *(x.scan.d++) - *(y.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXMulYD(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_d); // range check is effective only when _DEBUG is defined.
	while (x.scan.d != x.end.d)
	{
		*(z.scan.d++) = *(x.scan.d++) * *(y.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXDivYD(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_d); // range check is effective only when _DEBUG is defined.
	while (x.scan.d != x.end.d)
	{
		*(z.scan.d++) = *(x.scan.d++) / *(y.scan.d++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZAddEqXMulYsD(BLRange z, BLCRange x, BLCPtr ys)
{
	BLRange_Check2DBG(&z, &x, BLType_d);
	while (x.scan.d != x.end.d)
	{
		*(z.scan.d++) += *(x.scan.d++) * (*ys.d);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXInnerProductYD(BLPtr z, BLCRange x, BLCRange y)
{
	BLRange_Check2CDBG(&x, &y, BLType_d);
	*z.d = 0.0;
	while (x.scan.d != x.end.d)
	{
		*z.d += (*(x.scan.d++)) * (*(y.scan.d++));
	}
	BLBlas_Return(__FILE__, __LINE__);
}

void BLBlas_ZsEqXsD(BLPtr zs, BLCPtr xs)
{
	*zs.d = *xs.d;
}

void BLBlas_ZsEqNegateXsD(BLPtr zs, BLCPtr xs)
{
	*zs.d = -(*xs.d);
}

void BLBlas_ZsEqReciprocalXsD(BLPtr zs, BLCPtr xs)
{
	*zs.d = 1.0 / *xs.d;
}
void BLBlas_ZsEqZeroD(BLPtr zs)
{
	*zs.d = 0.0;
}
void BLBlas_ZsEqOneD(BLPtr zs)
{
	*zs.d = 1.0;
}
float BLBlas_NormD(BLCPtr xs)
{
	return (float)((*xs.d) * (*xs.d));
}
#pragma endregion double operations

#pragma region float complex operations
#pragma region float complex _1v0c operations
int BLBlas_ZEqZeroFc(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_fc);
	while (z.scan.fc != z.end.fc)
	{
		*z.scan.fc++ = _FCOMPLEX_(0.0f, 0.0f);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqOneFc(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_fc);
	while (z.scan.fc != z.end.fc)
	{
		*z.scan.fc++ = _FCOMPLEX_(1.0f, 0.0f);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqMinusOneFc(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_fc);
	while (z.scan.fc != z.end.fc)
	{
		*z.scan.fc++ = _FCOMPLEX_(-1.0f, 0.0f);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion float complex _1v0c operations

#pragma region _1v1c float complex operations
int BLBlas_ZEqXFc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		*(z.scan.fc++) = *(x.scan.fc++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZAddEqXFc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		z.scan.fc->_Val[0] += x.scan.fc->_Val[0];
		z.scan.fc->_Val[1] += x.scan.fc->_Val[1];
		z.scan.fc++;
		x.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZSubEqXFc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		z.scan.fc->_Val[0] -= x.scan.fc->_Val[0];
		z.scan.fc->_Val[1] -= x.scan.fc->_Val[1];
		z.scan.fc++;
		x.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZMulEqXFc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		*(z.scan.fc) = _FCmulcc(*z.scan.fc++, *x.scan.fc++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZDivEqXFc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		float _1_normx = 1.0f / normf(*x.scan.fc);
		float a = crealf(*z.scan.fc);
		float b = cimagf(*z.scan.fc);
		float c = crealf(*x.scan.fc);
		float d = cimagf(*x.scan.fc);
		*z.scan.fc++ = _FCOMPLEX_(_1_normx * (a*c + b * d), _1_normx * (b*c - a * d));
		x.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqNegateXFc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		float re_x = crealf(*x.scan.fc);
		float im_x = cimagf(*x.scan.fc++);
		*(z.scan.fc++) = _FCOMPLEX_(-re_x, -im_x);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqReciprocalXFc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		float re_x = crealf(*x.scan.fc);
		float im_x = cimagf(*x.scan.fc++);
		float _1_normx = 1.0f / (re_x * re_x + im_x * im_x);
		*(z.scan.fc++) = _FCOMPLEX_(re_x * _1_normx, -im_x * _1_normx);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZMulEqXsFc(BLRange z, BLCPtr x)
{
	BLRange_Check1DBG(&z, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.fc != z.end.fc)
	{
		*z.scan.fc = _FCmulcc(*z.scan.fc, *x.fc);
		z.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

#pragma endregion _1v1c float complex operations

#pragma region _2v float complex operations
int BLBlas_SwapFc(BLRange x, BLRange y)
{
	BLRange_Check2VDBG(&x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.fc != x.end.fc)
	{
		_Fcomplex fc = *(x.scan.fc);
		*(x.scan.fc++) = *(y.scan.fc);
		*(y.scan.fc++) = fc;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion _2v float complex operations
#pragma region _1v2c float complex operations
int BLBlas_ZEqXAddYFc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.fc != x.end.fc)
	{
		*(z.scan.fc++) = _FCOMPLEX_(
			crealf(*x.scan.fc) + crealf(*y.scan.fc),
			cimagf(*x.scan.fc) + cimagf(*y.scan.fc)
		);
		x.scan.fc++;
		y.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXSubYFc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.fc != x.end.fc)
	{
		*(z.scan.fc++) = _FCOMPLEX_(
			crealf(*x.scan.fc) - crealf(*y.scan.fc),
			cimagf(*x.scan.fc) - cimagf(*y.scan.fc)
		);
		x.scan.fc++;
		y.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXMulYFc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.fc != x.end.fc)
	{
		*(z.scan.fc++) = _FCmulcc(
			*x.scan.fc, *y.scan.fc
		);
		x.scan.fc++;
		y.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXDivYFc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.fc != x.end.fc)
	{
		float re_x = crealf(*x.scan.fc);
		float im_x = cimagf(*x.scan.fc);
		float re_y = crealf(*y.scan.fc);
		float im_y = cimagf(*y.scan.fc);
		float _1_normy = 1.0f / (re_y * re_y + im_y * im_y);

		*(z.scan.fc++) = _FCOMPLEX_(
			_1_normy * (re_x * re_y + im_x * im_y),
			_1_normy * (im_x * re_y - re_x * im_y)
		);
		x.scan.fc++;
		y.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZAddEqXMulYsFc(BLRange z, BLCRange x, BLCPtr ys)
{
	BLRange_Check2DBG(&z, &x, BLType_d);
	while (x.scan.fc != x.end.fc)
	{
		*(z.scan.fc) = _FCaddcc(*z.scan.fc, _FCmulcc(*x.scan.fc, *ys.fc));
		z.scan.fc++;
		x.scan.fc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZEqXInnerProductYFc(BLPtr z, BLCRange x, BLCRange y)
{
	BLRange_Check2CDBG(&x, &y, BLType_d);
	*z.fc = _FCOMPLEX_(0.0f, 0.0f);
	while (x.scan.fc != x.end.fc)
	{
		*z.fc = _FCaddcc(*z.fc, _FCmulcc(*x.scan.fc++, conjf(*y.scan.fc++)));
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion _1v2c float complex operations

void BLBlas_ZsEqXsFc(BLPtr zs, BLCPtr xs)
{
	*zs.fc = *xs.fc;
}

void BLBlas_ZsEqConjXsFc(BLPtr zs, BLCPtr xs)
{
	*zs.fc = conjf(*xs.fc);
}

void BLBlas_ZsEqNegateXsFc(BLPtr zs, BLCPtr xs)
{
	zs.fc->_Val[0] = -(xs.fc->_Val[0]);
	zs.fc->_Val[1] = -(xs.fc->_Val[1]);
}

void BLBlas_ZsEqReciprocalXsFc(BLPtr zs, BLCPtr xs)
{
	float _1_norm_xs = 1.0f / normf(*xs.fc);
	*zs.fc = _FCmulcr(conjf(*xs.fc), _1_norm_xs);
}

void BLBlas_ZsEqZeroFc(BLPtr zs)
{
	*zs.fc = _FCOMPLEX_(0.0f, 0.0f);
}

void BLBlas_ZsEqOneFc(BLPtr zs)
{
	*zs.fc = _FCOMPLEX_(1.0f, 0.0f);
}

float BLBlas_NormFc(BLCPtr xs)
{
	return normf(*xs.fc);
}

#pragma endregion float complex operations

#pragma region double complex operations
#pragma region double complex _1v0c operations
int BLBlas_ZEqZeroDc(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_fc);
	while (z.scan.dc != z.end.dc)
	{
		*z.scan.dc++ = _DCOMPLEX_(0.0f, 0.0f);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqOneDc(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_fc);
	while (z.scan.dc != z.end.dc)
	{
		*z.scan.dc++ = _DCOMPLEX_(1.0f, 0.0f);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqMinusOneDc(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_fc);
	while (z.scan.dc != z.end.dc)
	{
		*z.scan.dc++ = _DCOMPLEX_(-1.0f, 0.0f);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion double complex _1v0c operations

#pragma region _1v1c double complex operations
int BLBlas_ZEqXDc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		*(z.scan.dc++) = *(x.scan.dc++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZAddEqXDc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		z.scan.dc->_Val[0] += x.scan.dc->_Val[0];
		z.scan.dc->_Val[1] += x.scan.dc->_Val[1];
		z.scan.dc++;
		x.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZSubEqXDc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		z.scan.dc->_Val[0] -= x.scan.dc->_Val[0];
		z.scan.dc->_Val[1] -= x.scan.dc->_Val[1];
		z.scan.dc++;
		x.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZMulEqXDc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		*(z.scan.dc) = _Cmulcc(*z.scan.dc++, *x.scan.dc++);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZDivEqXDc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		double _1_normx = 1.0 / norm(*x.scan.dc);
		double a = creal(*z.scan.dc);
		double b = cimag(*z.scan.dc);
		double c = creal(*x.scan.dc);
		double d = cimag(*x.scan.dc);
		*z.scan.dc++ = _DCOMPLEX_(_1_normx * (a*c + b * d), _1_normx * (b*c - a * d));
		x.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqNegateXDc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		double re_x = creal(*x.scan.dc);
		double im_x = cimag(*x.scan.dc++);
		*(z.scan.dc++) = _DCOMPLEX_(-re_x, -im_x);
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqReciprocalXDc(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		double re_x = creal(*x.scan.dc);
		double im_x = cimag(*x.scan.dc++);
		double _1_normx = 1.0 / (re_x * re_x + im_x * im_x);
		*(z.scan.dc++) = _DCOMPLEX_(re_x * _1_normx, -im_x * _1_normx);
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZMulEqXsDc(BLRange z, BLCPtr x)
{
	BLRange_Check1DBG(&z, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (z.scan.dc != z.end.dc)
	{
		*z.scan.dc = _Cmulcc(*z.scan.dc, *x.dc);
		z.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

#pragma endregion _1v1c double complex operations

#pragma region _2v double complex operations
int BLBlas_SwapDc(BLRange x, BLRange y)
{
	BLRange_Check2VDBG(&x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.dc != x.end.dc)
	{
		_Dcomplex fc = *(x.scan.dc);
		*(x.scan.dc++) = *(y.scan.dc);
		*(y.scan.dc++) = fc;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion _2v double complex operations
#pragma region _1v2c double complex operations
int BLBlas_ZEqXAddYDc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.dc != x.end.dc)
	{
		*(z.scan.dc++) = _DCOMPLEX_(
			creal(*x.scan.dc) + creal(*y.scan.dc),
			cimag(*x.scan.dc) + cimag(*y.scan.dc)
		);
		x.scan.dc++;
		y.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXSubYDc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.dc != x.end.dc)
	{
		*(z.scan.dc++) = _DCOMPLEX_(
			creal(*x.scan.dc) - creal(*y.scan.dc),
			cimag(*x.scan.dc) - cimag(*y.scan.dc)
		);
		x.scan.dc++;
		y.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXMulYDc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.dc != x.end.dc)
	{
		*(z.scan.dc++) = _Cmulcc(
			*x.scan.dc, *y.scan.dc
		);
		x.scan.dc++;
		y.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}

int BLBlas_ZEqXDivYDc(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_fc); // range check is effective only when _DEBUG is defined.
	while (x.scan.dc != x.end.dc)
	{
		double re_x = creal(*x.scan.dc);
		double im_x = cimag(*x.scan.dc);
		double re_y = creal(*y.scan.dc);
		double im_y = cimag(*y.scan.dc);
		double _1_normy = 1.0 / (re_y * re_y + im_y * im_y);

		*(z.scan.dc++) = _DCOMPLEX_(
			_1_normy * (re_x * re_y + im_x * im_y),
			_1_normy * (im_x * re_y - re_x * im_y)
		);
		x.scan.dc++;
		y.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZAddEqXMulYsDc(BLRange z, BLCRange x, BLCPtr ys)
{
	BLRange_Check2DBG(&z, &x, BLType_d);
	while (x.scan.dc != x.end.dc)
	{
		*(z.scan.dc) = _Caddcc(*z.scan.dc, _Cmulcc(*x.scan.dc, *ys.dc));
		z.scan.dc++;
		x.scan.dc++;
	}
	BLBlas_Return(__FILE__, __LINE__);
}
int BLBlas_ZEqXInnerProductYDc(BLPtr z, BLCRange x, BLCRange y)
{
	BLRange_Check2CDBG(&x, &y, BLType_d);
	*z.dc = _DCOMPLEX_(0.0f, 0.0f);
	while (x.scan.dc != x.end.dc)
	{
		*z.dc = _Caddcc(*z.dc, _Cmulcc(*x.scan.dc++, conj(*y.scan.dc++)));
	}
	BLBlas_Return(__FILE__, __LINE__);
}
#pragma endregion _1v2c double complex operations

void BLBlas_ZsEqXsDc(BLPtr zs, BLCPtr xs)
{
	*zs.dc = *xs.dc;
}

void BLBlas_ZsEqConjXsDc(BLPtr zs, BLCPtr xs)
{
	*zs.dc = conj(*xs.dc);
}

void BLBlas_ZsEqNegateXsDc(BLPtr zs, BLCPtr xs)
{
	zs.dc->_Val[0] = -(xs.dc->_Val[0]);
	zs.dc->_Val[1] = -(xs.dc->_Val[1]);
}

void BLBlas_ZsEqReciprocalXsDc(BLPtr zs, BLCPtr xs)
{
	double _1_norm_xs = 1.0 / norm(*xs.dc);
	*zs.dc = _Cmulcr(conj(*xs.dc), _1_norm_xs);
}

void BLBlas_ZsEqZeroDc(BLPtr zs)
{
	*zs.dc = _DCOMPLEX_(0.0, 0.0);
}

void BLBlas_ZsEqOneDc(BLPtr zs)
{
	*zs.dc = _DCOMPLEX_(1.0, 0.0);
}

float BLBlas_NormDc(BLCPtr xs)
{
	return (float)norm(*xs.dc);
}


#pragma endregion double complex operations


const BLBlasInterface BLBlasInterfaces[] =
{
	{
		BLBlas_ZEqOneF,
		BLBlas_ZEqZeroF,
		BLBlas_ZEqMinusOneF,

		BLBlas_ZEqXF,
		BLBlas_ZAddEqXF,
		BLBlas_ZSubEqXF,
		BLBlas_ZMulEqXF,
		BLBlas_ZDivEqXF,
		BLBlas_ZEqNegateXF,
		BLBlas_ZEqReciprocalXF,
		BLBlas_ZMulEqXsF,

		BLBlas_SwapF,

		BLBlas_ZEqXAddYF,
		BLBlas_ZEqXSubYF,
		BLBlas_ZEqXMulYF,
		BLBlas_ZEqXDivYF,
		BLBlas_ZAddEqXMulYsF,
		BLBlas_ZEqXInnerProductYF,

		BLBlas_ZsEqXsF,
		BLBlas_ZsEqXsF,
		BLBlas_ZsEqNegateXsF,
		BLBlas_ZsEqReciprocalXsF,
		BLBlas_ZsEqZeroF,
		BLBlas_ZsEqOneF,
		BLBlas_NormF,
		BLType_f
	},
	{
		BLBlas_ZEqOneD,
		BLBlas_ZEqZeroD,
		BLBlas_ZEqMinusOneD,

		BLBlas_ZEqXD,
		BLBlas_ZAddEqXD,
		BLBlas_ZSubEqXD,
		BLBlas_ZMulEqXD,
		BLBlas_ZDivEqXD,
		BLBlas_ZEqNegateXD,
		BLBlas_ZEqReciprocalXD,
		BLBlas_ZMulEqXsD,

		BLBlas_SwapD,

		BLBlas_ZEqXAddYD,
		BLBlas_ZEqXSubYD,
		BLBlas_ZEqXMulYD,
		BLBlas_ZEqXDivYD,
		BLBlas_ZAddEqXMulYsD,
		BLBlas_ZEqXInnerProductYD,

		BLBlas_ZsEqXsD,
		BLBlas_ZsEqXsD,
		BLBlas_ZsEqNegateXsD,
		BLBlas_ZsEqReciprocalXsD,
		BLBlas_ZsEqZeroD,
		BLBlas_ZsEqOneD,
		BLBlas_NormD,
		BLType_d
	},
	{
		BLBlas_ZEqOneFc,
		BLBlas_ZEqZeroFc,
		BLBlas_ZEqMinusOneFc,

		BLBlas_ZEqXFc,
		BLBlas_ZAddEqXFc,
		BLBlas_ZSubEqXFc,
		BLBlas_ZMulEqXFc,
		BLBlas_ZDivEqXFc,
		BLBlas_ZEqNegateXFc,
		BLBlas_ZEqReciprocalXFc,
		BLBlas_ZMulEqXsFc,

		BLBlas_SwapFc,

		BLBlas_ZEqXAddYFc,
		BLBlas_ZEqXSubYFc,
		BLBlas_ZEqXMulYFc,
		BLBlas_ZEqXDivYFc,
		BLBlas_ZAddEqXMulYsFc,
		BLBlas_ZEqXInnerProductYFc,

		BLBlas_ZsEqXsFc,
		BLBlas_ZsEqConjXsFc,
		BLBlas_ZsEqNegateXsFc,
		BLBlas_ZsEqReciprocalXsFc,
		BLBlas_ZsEqZeroFc,
		BLBlas_ZsEqOneFc,
		BLBlas_NormFc,
		BLType_fc
	},
	{
		BLBlas_ZEqOneDc,
		BLBlas_ZEqZeroDc,
		BLBlas_ZEqMinusOneDc,

		BLBlas_ZEqXDc,
		BLBlas_ZAddEqXDc,
		BLBlas_ZSubEqXDc,
		BLBlas_ZMulEqXDc,
		BLBlas_ZDivEqXDc,
		BLBlas_ZEqNegateXDc,
		BLBlas_ZEqReciprocalXDc,
		BLBlas_ZMulEqXsDc,

		BLBlas_SwapDc,

		BLBlas_ZEqXAddYDc,
		BLBlas_ZEqXSubYDc,
		BLBlas_ZEqXMulYDc,
		BLBlas_ZEqXDivYDc,
		BLBlas_ZAddEqXMulYsDc,
		BLBlas_ZEqXInnerProductYDc,

		BLBlas_ZsEqXsDc,
		BLBlas_ZsEqConjXsDc,
		BLBlas_ZsEqNegateXsDc,
		BLBlas_ZsEqReciprocalXsDc,
		BLBlas_ZsEqZeroDc,
		BLBlas_ZsEqOneDc,
		BLBlas_NormDc,
		BLType_dc
	}
};

PCBLBlasInterface BLBlas_GetInterface(BLTypes t)
{
	return ((int)BLType_dc >= (int)t) && ((int)t >= (int)BLType_f) ?
		&BLBlasInterfaces[(int)t - (int)BLType_f] : NULL;
}
