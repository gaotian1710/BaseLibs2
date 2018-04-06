#pragma once
#if defined(__cplusplus)
extern "C" {
#endif
	// naming convention
	// Zp, Xp, Yp : pointers are post-incremented.
	// Zf, Xf, Yf : pointers are fixed.
	// F: float
	// Fc: float complex
	// D: double
	// Dc: double complex

	// 1v0c operations
	void BLBlas_ZpEqZeroF(PBLPtr z);
	void BLBlas_ZpEqOneF(PBLPtr z);
	void BLBlas_ZpEqNegativeOneF(PBLPtr z);
	void BLBlas_ZpEqZeroD(PBLPtr z);
	void BLBlas_ZpEqOneD(PBLPtr z);
	void BLBlas_ZpEqNegativeOneD(PBLPtr z);
	void BLBlas_ZpEqZeroFc(PBLPtr z);
	void BLBlas_ZpEqOneFc(PBLPtr z);
	void BLBlas_ZpEqNegativeOneFc(PBLPtr z);
	void BLBlas_ZpEqZeroDc(PBLPtr z);
	void BLBlas_ZpEqOneDc(PBLPtr z);
	void BLBlas_ZpEqNegativeOneDc(PBLPtr z);

	// 1v1c operations
	void BLBlas_ZpEqXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpAddEqXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpSubEqXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpMulEqXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpDivEqXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqNegativeXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqReciprocalXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpAddEqXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpSubEqXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpMulEqXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpDivEqXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqNegativeXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqReciprocalXpD(PBLPtr z, PBLCPtr x);

	void BLBlas_ZpEqXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpAddEqXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpSubEqXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpMulEqXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpDivEqXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqNegativeXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqReciprocalXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqConjugateXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpAddEqXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpSubEqXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpMulEqXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpDivEqXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqNegativeXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqReciprocalXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpEqConjugateXpDc(PBLPtr z, PBLCPtr x);

	void BLBlas_ZpfEqAddEqXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpfEqMulEqXpF(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpfEqAddEqXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpfEqMulEqXpD(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpfEqAddEqXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpfEqMulEqXpFc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpfEqAddEqXpDc(PBLPtr z, PBLCPtr x);
	void BLBlas_ZpfEqMulEqXpDc(PBLPtr z, PBLCPtr x);
#if defined(__cplusplus)
}
#endif
