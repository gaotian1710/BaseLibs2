#pragma once
/*!
\file BLWinPath.h
\brief extension utilities of windows path management APIs
*/
#if defined(__cplusplus)
extern "C" {
#endif

	/*!
	\brief get abosolute path of the most prioritized executable module in the current
		process. The prioritization is specified by nameOfCandidates.
	\param nameOfCandidates [in] an array of LPCWSTR. the last element must be NULL.
	\return the absolute path of the module.
	*/
	PBLArray BLWinPath_GetModulePath(const wchar_t* *namesOfCandidates);

	/*!
	\brief check if the parent folder exist and has write permission.
	\param filePath [in] the file path to create.
	\return win32 error code, ERROR_PATH_NOT_FOUND, ERROR_ACCESS_DENIED, etc.
	*/
	DWORD BLWinPath_CanWrite(const wchar_t* filePath);

	/*!
	\brief force to move the file even if the destination file already exists.
	\param srcFilePath [in] the source file path
	\param dstFilePath [in] the desitnation file path
	\return win32 error code
	*/
	DWORD BLWinPath_MoveFile(const wchar_t* srcFilePath, const wchar_t* dstFilePath);
#if defined(__cplusplus)
}
#endif

