// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int wmain(int argc, const wchar_t* argv[]) 
{
	PBLArray p = BLArray_New(2, BLType_i16);
	printf("sizeof(BLArray) = %d, sizeof(BLData) = %d, sizeof(BLPtr) = %d, sizeof(BLData1) = %d\n",
		sizeof(BLArray), sizeof(BLData), sizeof(BLPtr), sizeof(BLData1));
	printf("p = 0x%08x\n", (uint32_t)p);
	printf("p->data.i16 = 0x%08x\n", (uint32_t)(p->data.i16));
	printf("p->end.i16 = 0x%08x\n", (uint32_t)(p->end.i16));
	printf("_CrtCheckMemory() = %d\n", _CrtCheckMemory());
	for (size_t i = 0; i < 8; i++)
	{
		p->data.i16[i] = (int16_t)(i * 8);
		printf("i = %d: _CrtCheckMemory() = %d\n", i, _CrtCheckMemory());
	}
	for (size_t i = 0; i < 8; i++)
	{
		printf("data.i16[i] = %d\n", p->data.i16[i]);
	}
	BLArray_Delete(&p);
	_CrtDumpMemoryLeaks();
	return 0;
}