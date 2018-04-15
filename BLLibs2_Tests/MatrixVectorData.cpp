#include "stdafx.h"
#include "CppUnitTest.h"
#include "MatrixVectorData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLibs2_Tests
{		
	MatrixVectorData::MatrixVectorData()
	{
	}
	MatrixVectorData::~MatrixVectorData()
	{
	}

	const double MatrixVectorData::tolD = 1.0e-10;
	const float MatrixVectorData::tolF = 1.0e-5f;

#pragma region float test data
	const float MatrixVectorData::a2x3F[] =
	{
		1.0f, 2.0f, 3.0f,
		6.0f, 5.0f, 4.0f
	};

	const float MatrixVectorData::a3x2F[] =
	{
		1.0f, 2.0f,
		4.0f, 3.0f,
		5.0f, 6.0f
	};
	const float MatrixVectorData::a2x3tF[] =
	{
		a2x3F[0], a2x3F[3],
		a2x3F[1], a2x3F[4],
		a2x3F[2], a2x3F[5]
	};
	const float MatrixVectorData::a3x3F[] =
	{
		1.0f, 2.0f, 3.0f,
		6.0f, 5.0f, 4.0f,
		-5.5f, -8.0f, -9.0f
	};
	const float MatrixVectorData::u3x3F[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	const float MatrixVectorData::a4x5F[] =
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, a2x3F[0], a2x3F[1], a2x3F[2], 0.0f,
		0.0f, a2x3F[3], a2x3F[4], a2x3F[5], 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	const float MatrixVectorData::a4x5F2[] =
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, a2x3F[4], a2x3F[5], 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
#pragma endregion float test data

#pragma region double test data
	const double MatrixVectorData::a2x3D[] =
	{
		1.0, 2.0, 3.0,
		6.0, 5.0, 4.0
	};

	const double MatrixVectorData::a3x2D[] =
	{
		1.0, 2.0,
		4.0, 3.0,
		5.0, 6.0
	};
	const double MatrixVectorData::a2x3tD[] =
	{
		a2x3D[0], a2x3D[3],
		a2x3D[1], a2x3D[4],
		a2x3D[2], a2x3D[5]
	};
	const double MatrixVectorData::a3x3D[] =
	{
		1.0, 2.0, 3.0,
		6.0, 5.0, 4.0,
		-5.5, -8.0, -9.0
	};
	const double MatrixVectorData::u3x3D[] =
	{
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};
#pragma endregion double test data

#pragma region float complex test data
	const _Fcomplex MatrixVectorData::a2x3Fc[] =
	{
		_FCOMPLEX_(1.0f, -1.0f), _FCOMPLEX_(2.0f, -2.0f), _FCOMPLEX_(3.0f, -3.0),
		_FCOMPLEX_(6.0f, 0.0f), _FCOMPLEX_(5.0f, 0.0f), _FCOMPLEX_(4.0f, 0.0f)
	};

	const _Fcomplex MatrixVectorData::a3x2Fc[] =
	{
		_FCOMPLEX_(1.0f, 0.0f), _FCOMPLEX_(2.0f, 0.0f),
		_FCOMPLEX_(4.0f, -4.0f), _FCOMPLEX_(3.0f, -3.0f),
		_FCOMPLEX_(5.0f, 0.0f), _FCOMPLEX_(6.0, 0.0f)
	};
	const _Fcomplex MatrixVectorData::a2x3tFc[] =
	{
		a2x3Fc[0], a2x3Fc[3],
		a2x3Fc[1], a2x3Fc[4],
		a2x3Fc[2], a2x3Fc[5]
	};
	const _Fcomplex MatrixVectorData::a3x3Fc[] =
	{
		a2x3Fc[0], a2x3Fc[1], a2x3Fc[2],
		a2x3Fc[3], a2x3Fc[4], a2x3Fc[5],
		_FCOMPLEX_(5.5f, 7.0f), _FCOMPLEX_(8.0f, 8.0f), _FCOMPLEX_(9.0f, 9.0f)
	};
	const _Fcomplex MatrixVectorData::u3x3Fc[] =
	{
		_FCOMPLEX_(1.0f, 0.0f), _FCOMPLEX_(0.0f, 0.0f), _FCOMPLEX_(0.0f, 0.0f),
		_FCOMPLEX_(0.0f, 0.0f), _FCOMPLEX_(1.0f, 0.0f), _FCOMPLEX_(0.0f, 0.0f),
		_FCOMPLEX_(0.0f, 0.0f), _FCOMPLEX_(0.0f, 0.0f), _FCOMPLEX_(1.0f, 0.0f)
	};
#pragma endregion float complex test data

#pragma region double complex test data
	const _Dcomplex MatrixVectorData::a2x3Dc[] =
	{
		_DCOMPLEX_(1.0, -1.0), _DCOMPLEX_(2.0, -2.0), _DCOMPLEX_(3.0, -3.0),
		_DCOMPLEX_(6.0, 0.0), _DCOMPLEX_(5.0, 0.0), _DCOMPLEX_(4.0, 0.0)
	};

	const _Dcomplex MatrixVectorData::a3x2Dc[] =
	{
		_DCOMPLEX_(1.0, 0.0), _DCOMPLEX_(2.0, 0.0),
		_DCOMPLEX_(4.0, -4.0), _DCOMPLEX_(3.0, -3.0),
		_DCOMPLEX_(5.0, 0.0), _DCOMPLEX_(6.0, 0.0)
	};
	const _Dcomplex MatrixVectorData::a2x3tDc[] =
	{
		a2x3Dc[0], a2x3Dc[3],
		a2x3Dc[1], a2x3Dc[4],
		a2x3Dc[2], a2x3Dc[5]
	};
	const _Dcomplex MatrixVectorData::a3x3Dc[] =
	{
		a2x3Dc[0], a2x3Dc[1], a2x3Dc[2],
		a2x3Dc[3], a2x3Dc[4], a2x3Dc[5],
		_DCOMPLEX_(5.5, 7.0), _DCOMPLEX_(8.0, 8.0), _DCOMPLEX_(9.0, 9.0)
	};
	const _Dcomplex MatrixVectorData::u3x3Dc[] =
	{
		_DCOMPLEX_(1.0, 0.0), _DCOMPLEX_(0.0, 0.0), _DCOMPLEX_(0.0, 0.0),
		_DCOMPLEX_(0.0, 0.0), _DCOMPLEX_(1.0, 0.0), _DCOMPLEX_(0.0, 0.0),
		_DCOMPLEX_(0.0, 0.0), _DCOMPLEX_(0.0, 0.0), _DCOMPLEX_(1.0, 0.0)
	};

#pragma endregion double complex test data
}