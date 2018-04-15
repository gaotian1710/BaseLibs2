#pragma once
namespace BaseLibs2_Tests
{
	class MatrixVectorData
	{
	public:
		MatrixVectorData();
		~MatrixVectorData();

		// tolerances for Assert:AreEqual()
		static const float tolF;
		static const double tolD;

		// test data
		static const float a2x3F[]; // 2x3 matrix source data
		static const float a3x2F[]; // 3x2 matrix source data
		static const float a2x3tF[]; // transpose of a2x3F
		static const float a3x3F[]; // 3x3 matrix source data
		static const float u3x3F[]; // 3x3 unit matrix
		static const float a4x5F[]; // 5x4 matrix as a reference result of submatrix copy
		static const float a4x5F2[];

		static const double a2x3D[]; // 2x3 matrix source data
		static const double a3x2D[]; // 3x2 matrix source data
		static const double a2x3tD[]; // transpose of a2x3F
		static const double a3x3D[]; // 3x3 matrix source data
		static const double u3x3D[]; // 3x3 unit matrix

		static const _Fcomplex a2x3Fc[]; // 2x3 matrix source data
		static const _Fcomplex a3x2Fc[]; // 3x2 matrix source data
		static const _Fcomplex a2x3tFc[]; // transpose of a2x3F
		static const _Fcomplex a3x3Fc[]; // 3x3 matrix source data
		static const _Fcomplex u3x3Fc[]; // 3x3 unit matrix

		static const _Dcomplex a2x3Dc[]; // 2x3 matrix source data
		static const _Dcomplex a3x2Dc[]; // 3x2 matrix source data
		static const _Dcomplex a2x3tDc[]; // transpose of a2x3F
		static const _Dcomplex a3x3Dc[]; // 3x3 matrix source data
		static const _Dcomplex u3x3Dc[]; // 3x3 unit matrix
	};
}
