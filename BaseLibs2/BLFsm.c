#include "stdafx.h"
#include "BLError.h"
#include "BLArray.h"
#include "BLFsm.h"

CRITICAL_SECTION gBLFsmLock = { 0 };

void BLFsm_SInit()
{
	InitializeCriticalSection(&gBLFsmLock);
}

void BLFsm_SUnInit()
{
	DeleteCriticalSection(&gBLFsmLock);
}

void AHNone(PBLFsm fsm, PBLFsmMsg msg)
{
}

BLFsmResult SHNone(PBLFsm fsm, PBLFsmMsg msg)
{
	return BLFsmResult_Ignored;
}

BLFsmResult BLFsm_Transit(PBLFsm fsm, PBLFsm msg)
{
	fsm->msg = msg;
	PBLFsmState oldState = fsm->state;
	BLFsmResult result = fsm->state->sh(fsm, msg);
	if (result == BLFsm_Transit)
	{
		oldState->ahExit(fsm, msg);
		fsm->state->ahEnter(fsm, msg);
	}
	return result;
}

PBLFsmMsg BLFsmMsg_New(int msg, BLTypes t, size_t cUnit)
{
	size_t ccAlloc = sizeof(BLFsmMsg) + BLUnitSizes[t] * cUnit;
	PBLFsmMsg pmsg = (PBLFsmMsg)malloc(ccAlloc);
	pmsg->end.c = (const char*)pmsg + ccAlloc;
	pmsg->refc = 1;
	pmsg->msg = msg;
	pmsg->dataType = t;
	return pmsg;
}

int BLFsmMsg_AddRef(PBLFsmMsg msg)
{
	if (msg->refc < 0) return msg->refc;
	EnterCriticalSection(&gBLFsmLock);
	msg->refc++;
	LeaveCriticalSection(&gBLFsmLock);
	return msg->refc;
}

int BLFsmMsg_DelRef(PBLFsmMsg *ppmsg)
{
	int retValue = 0;
	PBLFsmMsg pmsg = *ppmsg;
	if (pmsg->refc < 0) return pmsg->refc;
	EnterCriticalSection(&gBLFsmLock);
	pmsg->refc--;
	if (pmsg->refc == 0)
	{
		free(pmsg);
		*ppmsg = NULL;
	}
	LeaveCriticalSection(&gBLFsmLock);
	return retValue;
}
