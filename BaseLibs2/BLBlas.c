#include "stdafx.h"
#include "BLTypes.h"
#include "BLBlas.h"

#pragma region _1v0c operations
void BLBlas_ZpEqZeroF(PBLPtr z)
{
	*(z->f++) = 0.0f;
}

void BLBlas_ZpEqOneF(PBLPtr z)
{
	*(z->f++) = 1.0f;
}

void BLBlas_ZpEqNegativeOneF(PBLPtr z)
{
	*(z->f++) = -1.0f;
}

void BLBlas_ZpEqZeroD(PBLPtr z)
{
	*(z->d++) = 0.0;
}

void BLBlas_ZpEqOneD(PBLPtr z)
{
	*(z->d++) = 1.0;
}

void BLBlas_ZpEqNegativeOneD(PBLPtr z)
{
	*(z->d++) = -1.0;
}

void BLBlas_ZpEqZeroFc(PBLPtr z)
{
	*(z->fc++) = _FCOMPLEX_(0.0f, 0.0f);
}

void BLBlas_ZpEqOneFc(PBLPtr z)
{
	*(z->fc++) = _FCOMPLEX_(1.0f, 0.0f);
}

void BLBlas_ZpEqNegativeOneFc(PBLPtr z)
{
	*(z->fc++) = _FCOMPLEX_(-1.0f, 0.0f);
}

void BLBlas_ZpEqZeroDc(PBLPtr z)
{
	*(z->dc++) = _DCOMPLEX_(0.0, 0.0);
}

void BLBlas_ZpEqOneDc(PBLPtr z)
{
	*(z->dc++) = _DCOMPLEX_(1.0, 0.0);
}

void BLBlas_ZpEqNegativeOneDc(PBLPtr z)
{
	*(z->dc++) = _DCOMPLEX_(-1.0, 0.0);
}

#pragma endregion _1v0c operations

#pragma region _1v1c operations
void BLBlas_ZpEqXpF(PBLPtr z, PBLCPtr x)
{
	*(z->f++) = *(x->f++);
}

void BLBlas_ZpAddEqXpF(PBLPtr z, PBLCPtr x)
{
	*(z->f++) += *(x->f++);
}

#pragma endregion _1v1c operations
