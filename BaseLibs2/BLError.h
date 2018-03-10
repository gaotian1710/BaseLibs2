#pragma once
typedef enum {
	BLErrorType_BL = 0,
	BLErrorType_Errno,
	BLErrorType_Win,
	BLErrorType_HRESULT,
	BLErrorType_Other
} BLErrorType;

typedef union {
	uint64_t u;
	struct {
		BLErrorType type;
		uint32_t err;
	} typedNumber;
} BLError, *PBLError;

const BLError *PCBLError;

#if defined(__cplusplus)
extern "C" {
#endif
	const wchar_t* BLError_TypeLabel(BLErrorType t);

	BLError BLError_MakeBL(int errorNumber);

	BLError BLError_MakeErrno(int errorNumber);

	BLError BLError_MakeWin(int errorNumber);

	BLError BLError_MakeHRESULT(int errorNumber);

	BLError BLError_MakeOther(int errorNumber);
#if defined(__cplusplus)
}
#endif
