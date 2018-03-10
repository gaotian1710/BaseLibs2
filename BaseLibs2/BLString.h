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
#if defined(__cplusplus)
}
#endif
