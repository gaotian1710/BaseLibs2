#include "stdafx.h"
#include "BLSfo.h"

COPYFILE2_MESSAGE_ACTION CALLBACK BLSfo_CopyFile2Callback(
	const COPYFILE2_MESSAGE* pmsg,
	PVOID pvContext // event handle to allow BLSfo_CopyFile to return.
) {
	COPYFILE2_MESSAGE_ACTION action = COPYFILE2_PROGRESS_CONTINUE;
	if (pmsg->Type == COPYFILE2_CALLBACK_STREAM_FINISHED)
	{
		PBLSfo_CallbackInfo0 info = (PBLSfo_CallbackInfo0)pvContext;
		info->err = SetEvent(info->h) ? ERROR_SUCCESS : GetLastError();
		action = COPYFILE2_PROGRESS_QUIET;
	}
	return action;
}

DWORD BLSfo_CopyFile(const wchar_t * src, const wchar_t * dst, BOOL force)
{
	DWORD err = ERROR_SUCCESS;
	BLSfo_CallbackInfo0 info = { NULL, ERROR_SUCCESS };
	BOOL bCancel = FALSE;
	COPYFILE2_EXTENDED_PARAMETERS cf2param = {
		sizeof(COPYFILE2_EXTENDED_PARAMETERS),
		0,
		&bCancel, // cancel flag
		BLSfo_CopyFile2Callback, // progress callback
		(PVOID)&info // progress context
	};
	do {
		if (PathFileExists(dst))
		{
			if (force)
			{
				err = BLSfo_DeleteFile(dst);
			}
			else
			{
				err = ERROR_FILE_EXISTS;
			}
			if (err) break;
		}
		if (NULL == (info.h = CreateEvent(NULL, TRUE, FALSE, NULL)))
		{
			err = GetLastError(); break;
		}

		HRESULT hr = CopyFile2(src, dst, &cf2param);
		if (FAILED(hr))
		{
			err = 0xffff & hr; break;
		}

		DWORD waitResult = WaitForSingleObject(info.h, BL_COPY_TIMEOUT);
		switch (waitResult)
		{
		case WAIT_OBJECT_0:
			err = info.err;
			break;
		case WAIT_TIMEOUT:
			err = ERROR_TIMEOUT;
			break;
		default:
			err = GetLastError();
			break;
		}
	} while (false);
	return err;
}

DWORD CALLBACK BLSfo_MoveFileProgressCallback(
	LARGE_INTEGER totalFileSize,
	LARGE_INTEGER totalBytesTransfered,
	LARGE_INTEGER streamSize,
	LARGE_INTEGER streamBytesTransfered,
	DWORD streamNumber,
	DWORD callbackReason,
	HANDLE hSourceFile,
	HANDLE hDestinationFile,
	LPVOID pvData
) {
	DWORD nextAction = PROGRESS_CONTINUE;
	printf("%I64d, %I64d\n", totalFileSize.QuadPart, totalBytesTransfered.QuadPart);
	if (totalFileSize.QuadPart == totalBytesTransfered.QuadPart)
	{
		PBLSfo_CallbackInfo0 info = (PBLSfo_CallbackInfo0)pvData;
		nextAction = PROGRESS_QUIET;
		info->err = SetEvent(info->h) ? ERROR_SUCCESS : GetLastError();
		printf("complete !\n");
	}
	return nextAction;
}

DWORD BLSfo_MoveFile(const wchar_t * src, const wchar_t * dst, BOOL force)
{
	DWORD err = ERROR_SUCCESS;
	BLSfo_CallbackInfo0 info = { NULL, ERROR_SUCCESS };
	do {
		if (!PathFileExists(src))
		{
			err = ERROR_FILE_NOT_FOUND; break;
		}
		if (PathFileExists(dst))
		{
			if (force)
			{
				err = BLSfo_DeleteFile(dst);
			}
			else
			{
				err = ERROR_FILE_EXISTS;
			}
			if (err) break;
		}
		if (NULL == (info.h = CreateEvent(NULL, TRUE, FALSE, NULL)))
		{
			err = GetLastError(); break;
		}

		if (MoveFileWithProgress(src, dst, BLSfo_MoveFileProgressCallback, &info,
			0))
		{
			break;
		}
		else
		{
			err = GetLastError();
			if (ERROR_NOT_SAME_DEVICE == (err = GetLastError()) &&
				!MoveFileWithProgress(src, dst, BLSfo_MoveFileProgressCallback, &info,
				MOVEFILE_COPY_ALLOWED))
			{
				err = GetLastError(); break;
			}
			else
			{
				break;
			}
		}

		DWORD waitResult = WaitForSingleObject(info.h, BL_COPY_TIMEOUT);
		switch (waitResult)
		{
		case WAIT_OBJECT_0:
			err = info.err;
			printf("event set, err = %d\n", err);
			break;
		case WAIT_TIMEOUT:
			err = ERROR_TIMEOUT;
			break;
		default:
			err = GetLastError();
			break;
		}
	} while (false);
	return err;
}

DWORD BLSfo_DeleteFile(const wchar_t * toDelete)
{
	DWORD err = ERROR_ACCESS_DENIED;
	do {
		DWORD retryCount = BL_DELETE_RETRY;
		BOOL deleted = false;
		do {
			if (PathFileExists(toDelete) == FALSE)
			{
				deleted = TRUE;
				err = ERROR_SUCCESS;
			}
			if (deleted || (deleted = DeleteFile(toDelete)))
			{
				if (PathFileExists(toDelete))
				{
					Sleep(BL_DELETE_CONFIRM_WAIT);
				}
				else
				{
					err = ERROR_SUCCESS;
				}
			}
			else
			{ // fail in delete
				err = GetLastError();
				if (retryCount > 1)
				{ // it is not the last iteration of retry
					Sleep(BL_DELETE_RETRY_WAIT);
				}
			}
		} while (err != ERROR_SUCCESS && --retryCount);
	} while (false);
	return err;
}
