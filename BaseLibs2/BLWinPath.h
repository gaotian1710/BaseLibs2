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
#if defined(__cplusplus)
}
#endif

