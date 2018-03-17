#include "stdafx.h"
#include "BLArray.h"
#include "BLString.h"
#include "BLStringBuilder.h"
#include "BLWinPath.h"

PBLArray BLWinPath_GetModulePath(const wchar_t ** namesOfCandidates)
{
	wchar_t pathBuffer[MAX_PATH];
	int ierr = 0;
	PBLArray path = NULL;
	do {
		HMODULE h = NULL;
		const wchar_t* name = NULL;
		for (int i = 0; (name = namesOfCandidates[i]) != NULL; i++)
		{
			h = GetModuleHandle(name);
			if (h) break;
		}
		if (h == NULL)
		{
			h = GetModuleHandle(NULL);
		}

		if (MAX_PATH == GetModuleFileName(h, pathBuffer, MAX_PATH))
		{
			break;
		}
		
		path = BLString_NewW(pathBuffer, 0);
	} while (false);
	return path;
}

DWORD BLWinPath_CanWrite(const wchar_t * filePath)
{
	DWORD err = ERROR_SUCCESS;
	LPWSTR path = _wcsdup(filePath);
	HANDLE h = INVALID_HANDLE_VALUE;
	do {
		*(PathFindFileName(path) - 1) = L'\0';
		if (!PathFileExists(path) || ((DWORD)PathIsDirectory(path) != FILE_ATTRIBUTE_DIRECTORY))
		{
			err = ERROR_PATH_NOT_FOUND;
			break;
		}

		if (PathFileExists(filePath)) // try to append to the file if the file exists.
		{ 
			if (PathIsDirectory(filePath) == (BOOL)FILE_ATTRIBUTE_DIRECTORY)
			{ // it means that the file could not be written as a normal file.
				err = ERROR_INVALID_OPERATION;
				break;
			}
			// try to append to the file but actually does not.
			h = CreateFile(filePath, FILE_APPEND_DATA, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (h != INVALID_HANDLE_VALUE)
			{
				if (!CloseHandle(h))
				{
					err = GetLastError(); break;
				}
				else
				{
					h = INVALID_HANDLE_VALUE;
					break;
				}
			}
		}
		else
		{ // try to create and delte the file
			h = CreateFile(filePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (h != INVALID_HANDLE_VALUE) // file was successfully created.
			{
				if (!CloseHandle(h)) // close the file handle before delete.
				{
					err = GetLastError(); break; // fail to close the file handle.
				}
				h = INVALID_HANDLE_VALUE;

				// delete file
				int maxIter = 4;
				while (PathFileExists(filePath) && --maxIter)
				{
					if (DeleteFile(filePath)) break;
					Sleep(10);
				}
				// fail to delete the file.
				if (PathFileExists(filePath))
				{
					err = GetLastError();
					if (err == ERROR_SUCCESS)
					{
						err = ERROR_ACCESS_DENIED; break;
					}
				}
			}
		}
	} while (false);
	if (path)
	{
		free(path);
	}
	if (h != INVALID_HANDLE_VALUE)
	{
		CloseHandle(h);
	}
	return err;
}

DWORD BLWinPath_MoveFile(const wchar_t * srcFilePath, const wchar_t * dstFilePath)
{
	DWORD err = ERROR_SUCCESS;
	do {
		int maxIter = 4;
		while (PathFileExists(dstFilePath) && --maxIter)
		{
			if (DeleteFile(dstFilePath))
			{
				err = ERROR_SUCCESS;
				break;
			}
			else
			{
				err = GetLastError();
				Sleep(10);
			}
		}

		if (err) break;
		if (!MoveFile(srcFilePath, dstFilePath))
		{
			err = GetLastError(); break;
		}
	} while (false);
	return err;
}
