#pragma once

#if defined(__cplusplus)
extern "C" {
#endif
	int BLTupleFormatter_c(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_wc(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_i8(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_i16(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_i32(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_i64(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_ui8(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_ui16(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_ui32(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_ui64(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_f(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_d(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_fc(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_dc(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_ptr(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

	int BLTupleFormatter_type(
		BLTupleColumnPosition pos, wchar_t* buffer, size_t bufferLength, const BLData1* data);

#if defined(__cplusplus)
}
#endif

