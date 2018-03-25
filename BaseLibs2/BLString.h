#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

	/*!
	\brief create a new string containing ASCII or multi-byte character string.
	\param str [in] source string
	\param cbBufferLength [in] buffer length of the array to create. if cbBufferLength <
		strlen(str), the buffer length is equal to strlen(str) + 1 including null termination.
	\return BLArray containing a copy of str.
	*/
	PBLArray BLString_NewA(const char* str, size_t cbBufferLength);

	/*!
	\brief create a new string containing wide character string.
	\param wstr [in] source string
	\param ccBufferLength [in] buffer length of the array to create. if ccBufferLength <
		wcslen(wstr), the buffer length is equal to wcslen(str) + 1 including null termination.
	\return BLArray containing a copy of wstr.
	*/
	PBLArray BLString_NewW(const wchar_t* wstr, size_t ccBufferLength);

	/*!
	\brief translate a multibyte string to a wide character string
	\param str [in] a multibyte string
	\return a wide character string equivalent to str.
	*/
	PBLArray BLString_mbc2wc(PBLArray str);

	/*!
	\brief translate a wide character string to a multibyte string.
	\param wstr [in] a wide character string
	\return a multibyte string equivalent to wstr.
	*/
	PBLArray BLString_wc2mbc(PBLArray wstr);

	/*!
	\brief modify a file path appending decimal number at the end of filename extension
	\param wstr [in] a wide character string
	\param num [in] 0 or positive integer less than 100; i.e. representable in two digits
	\return a new path string
	*/
	PBLArray BLString_ModifyPath0(const wchar_t* wstr, unsigned int i);

	/*!
	\brief modify a file path appending decimal number at the end of filename base
	\param wstr [in] a wide character string
	\param num [in] 0 or positive integer less than 100; i.e. representable in two digits
	\return a new path string
	*/
	PBLArray BLString_ModifyPath1(const wchar_t* wstr, unsigned int i);

	/*!
	\brief calculate 16 bit hash code of array of anything
	\param str [in] array of anything
	\return 16 bit hash number
	*/
	uint16_t BLString_Hash16(PBLArray p);

	uint16_t BLString_Hash16raw(const wchar_t* p);

	/*!
	\brief embed a string between two double quotation marks.
	\param wstr [in] source string of wide characters
	\return result string embedded between double quoatation marks.
	*/
	PBLArray BLString_CsvDoubleQuotedString(PCBLArray wstr);

	/*!
	\brief embed a string between two double quotation marks.
	\param wstr [in] source string of wide characters
	\return result string embedded between double quoatation marks.
	*/
	PBLArray BLString_CsvDoubleQuatedStringRaw(const wchar_t* wstr);
#if defined(__cplusplus)
}
#endif
