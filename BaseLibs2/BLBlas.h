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
	inline void BLBlas_ZpEqZeroF(PBLPtr z);			/*!< *z++ = (float)0.0 */
	inline void BLBlas_ZpEqOneF(PBLPtr z);			/*!< *z++ = (float)1.0 */
	inline void BLBlas_ZpEqNegativeOneF(PBLPtr z);	/*! *z++ = (float)(-1.0) */
	inline void BLBlas_ZpEqZeroD(PBLPtr z);			/*! *z++ = (double)0.0 */
	inline void BLBlas_ZpEqOneD(PBLPtr z);			/*! *z++ = (double)1.0 */
	inline void BLBlas_ZpEqNegativeOneD(PBLPtr z);	/*! *z++ = (double)(-1.0) */
	inline void BLBlas_ZpEqZeroFc(PBLPtr z);		/*! *z++ = _FCOMPLEX_(0.0, 0.0) */
	inline void BLBlas_ZpEqOneFc(PBLPtr z);			/*! *z++ = _FCOMPLEX_(1.0, 0.0) */
	inline void BLBlas_ZpEqNegativeOneFc(PBLPtr z);	/*! *z++ = _FCOMPLEX_(-1.0, 0.0) */
	inline void BLBlas_ZpEqZeroDc(PBLPtr z);		/*! *z++ = _DCOMPLEX_(0.0, 0.0) */
	inline void BLBlas_ZpEqOneDc(PBLPtr z);			/*! *z++ = _DCOMPLEX_(1.0, 0.0) */
	inline void BLBlas_ZpEqNegativeOneDc(PBLPtr z);	/*! *z++ = _DCOMPLEX_(-1.0, 0.0) */

	// 1v1c operations
	inline void BLBlas_ZpEqXpF(PBLPtr z, PBLCPtr x);			/*!< *z++ = *x++ */
	inline void BLBlas_ZpAddEqXpF(PBLPtr z, PBLCPtr x);			/*!< *z++ += *x++ */
	inline void BLBlas_ZpSubEqXpF(PBLPtr z, PBLCPtr x);			/*!< *z++ -= *x++ */
	inline void BLBlas_ZpMulEqXpF(PBLPtr z, PBLCPtr x);			/*!< *z++ *= *x++ */
	inline void BLBlas_ZpDivEqXpF(PBLPtr z, PBLCPtr x);			/*!< *z++ /= *x++ */
	inline void BLBlas_ZpEqNegativeXpF(PBLPtr z, PBLCPtr x);	/*!< *z++ = (-1.0) * *x++ */
	inline void BLBlas_ZpEqReciprocalXpF(PBLPtr z, PBLCPtr x);	/*!< *z++ = 1.0/*x++ */
	inline void BLBlas_ZpEqXpD(PBLPtr z, PBLCPtr x);			/*!< *z++ = *x++ */
	inline void BLBlas_ZpAddEqXpD(PBLPtr z, PBLCPtr x);			/*!< *z++ *= *x++ */
	inline void BLBlas_ZpSubEqXpD(PBLPtr z, PBLCPtr x);			/*!< *z++ -= *x++ */
	inline void BLBlas_ZpMulEqXpD(PBLPtr z, PBLCPtr x);			/*!< *z++ *= *x++ */
	inline void BLBlas_ZpDivEqXpD(PBLPtr z, PBLCPtr x);			/*!< *z++ /= *x++ */
	inline void BLBlas_ZpEqNegativeXpD(PBLPtr z, PBLCPtr x);	/*!< *z++ = (-1.0) * *x++ */
	inline void BLBlas_ZpEqReciprocalXpD(PBLPtr z, PBLCPtr x);	/*!< *z++ = 1.0/(*x++) */

	inline void BLBlas_ZpEqXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpAddEqXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpSubEqXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpMulEqXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpDivEqXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpEqNegativeXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpEqReciprocalXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpEqConjugateXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpEqXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpAddEqXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpSubEqXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpMulEqXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpDivEqXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpEqNegativeXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpEqReciprocalXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZpEqConjugateXpDc(PBLPtr z, PBLCPtr x);

	inline void BLBlas_ZfEqAddEqXpF(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZfEqMulEqXpF(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZfEqAddEqXpD(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZfEqMulEqXpD(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZfEqAddEqXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZfEqMulEqXpFc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZfEqAddEqXpDc(PBLPtr z, PBLCPtr x);
	inline void BLBlas_ZfEqMulEqXpDc(PBLPtr z, PBLCPtr x);
#if defined(__cplusplus)
}
#endif
