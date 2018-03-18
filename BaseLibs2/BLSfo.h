#pragma once
/*! \file BLSfo.h
\description a set of secure file operations with confirming completion of operations.
	windows.h needs to be included.
*/
// default timeout of BLSfo_CopyFile() in milliseconds
#define BL_COPY_TIMEOUT	20000
#define BL_DELETE_RETRY	8
#define BL_DELETE_RETRY_WAIT	1000
#define BL_DELETE_CONFIRM_WAIT	100

typedef struct {
	HANDLE h; // event handle
	DWORD err; // callback error code (win32 error code)
} BLSfo_CallbackInfo0, *PBLSfo_CallbackInfo0;


#if defined(__cplusplus)
extern "C" {
#endif
	/*!
	\brief copy a file from src to dst.
	\param src [in] absolute path of the source file.
	\param dst [in] absolute path of the destination file.
	\param force [in] if it is false, the operation fails with ERROR_FILE_EXISTS.
	\return win32 error code
	*/
	DWORD BLSfo_CopyFile(const wchar_t* src, const wchar_t* dst, BOOL force);

	/*!
	\brief move a file from src to dst.
	\param src [in] absolute path of the source file.
	\param dst [in] absolute path of the destination file.
	\param force [in] if it is false, the operation fails with ERROR_FILE_EXISTS.
	\return win32 error code
	*/
	DWORD BLSfo_MoveFile(const wchar_t* src, const wchar_t* dst, BOOL force);

	/*!
	\brief delete a file
	\param toDelete [in] absolute path of the file to delete
	\return win32 error code
	*/
	DWORD BLSfo_DeleteFile(const wchar_t* toDelete);

#if defined(__cplusplus)
}
#endif
