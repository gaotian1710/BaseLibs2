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
	return 0;
}

int BLBlas_ZEqOneF(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = 1.0f;
	}
	return 0;
}

int BLBlas_ZEqMinusOneF(BLRange z)
{
	BLRange_Check1DBG(&z, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = -1.0f;
	}
	return 0;
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
	return 0;
}

int BLBlas_ZAddEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) += *(x.scan.f++);
	}
	return 0;
}

int BLBlas_ZSubEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) -= *(x.scan.f++);
	}
	return 0;
}

int BLBlas_ZMulEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) *= *(x.scan.f++);
	}
	return 0;
}

int BLBlas_ZDivEqXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) /= *(x.scan.f++);
	}
	return 0;
}

int BLBlas_ZEqNegateXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = (-1.0f) * (*(x.scan.f++));
	}
	return 0;
}

int BLBlas_ZEqReciprocalXF(BLRange z, BLCRange x)
{
	BLRange_Check2DBG(&z, &x, BLType_f); // range check is effective only when _DEBUG is defined.
	while (z.scan.f != z.end.f)
	{
		*(z.scan.f++) = 1.0f / (*(x.scan.f++));
	}
	return 0;
}
#pragma endregion _1v0c operations
#pragma region _2v operations
int BLBlas_Swap(BLRange x, BLRange y)
{
	BLRange_Check2VDBG(&x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		float f = *(x.scan.f);
		*(x.scan.f++) = *(y.scan.f);
		*(y.scan.f++) = f;
	}
	return 0;
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
	return 0;
}
int BLBlas_ZEqXSubYF(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++) - *(y.scan.f++);
	}
	return 0;
}
int BLBlas_ZEqXMulYF(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++) * *(y.scan.f++);
	}
	return 0;
}
int BLBlas_ZEqXDivYF(BLRange z, BLCRange x, BLCRange y)
{
	BLRange_Check3DBG(&z, &x, &y, BLType_f); // range check is effective only when _DEBUG is defined.
	while (x.scan.f != x.end.f)
	{
		*(z.scan.f++) = *(x.scan.f++) / *(y.scan.f++);
	}
	return 0;
}
#pragma endregion _1v2c operations
#pragma endregion float operations
