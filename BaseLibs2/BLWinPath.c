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
		
		if (MAX_PATH == GetModuleFileName(h, pathBuffer, MAX_PATH))
		{
			break;
		}
		
		path = BLString_NewW(pathBuffer, 0);
	} while (false);
	return path;
}
