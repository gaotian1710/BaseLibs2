#pragma once

#if defined(__cplusplus)
extern "C" {
#endif
	/*!
	\brief create a new buffer to build a wide character string
	\param ccLength [in] initial length
	\return the pointer to the buffer
	*/
	PBLBuffer BLStringBuilder_New(size_t ccLength);

	/*!
	\brief append wide character string
	\param pp [in,out] pointer pointer to the buffer as a string builder
	\param wstr [in] a wide character string to append to **pp.data.wc
	\return ENOMEM or 0
	*/
	int BLStringBuilder_AppendW(PBLBuffer* pp, const wchar_t* wstr);

	int BLStringBuilder_AppendW2(PBLBuffer* pp, const wchar_t* wstr0, const wchar_t* wstr1);

	/*!
	\brief translate to wide character string and append multibyte character string
	\param pp [in,out] pointer pointer to the buffer as a string builder
	\param str [in] a multibyte character string to append to **pp.data.wc
	\return ENOMEM or 0
	*/
	int BLStringBuilder_AppendA(PBLBuffer* pp, const char* str);

	int BLStringBuilder_AppendA2(PBLBuffer* pp, const char* str0, const char* str1);

	/*!
	\brief get a wide character string from a string builder
	\param p [in] a buffer of as a string builder
	\return null or a pointer to a new array of wchar_t.
	*/
	PBLArray BLStringBuilder_GetW(PBLBuffer p);

	/*!
	\brief get a multibyte character string from a string builder
	\param p [in] a buffer of as a string builder
	\return null or a pointer to a new array of wchar_t.
	*/
	PBLArray BLStringBuilder_GetA(PBLBuffer p);

#if defined(__cplusplus)
}
#endif
