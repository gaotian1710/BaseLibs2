#pragma once

typedef struct _BLFsmMsg {
	int refc; //  reference counter, negative value means that it does not need free.
	int msg;
	BLTypes dataType;
	BLCPtr end;
	BLData data;
} BLFsmMsg, *PBLFsmMsg;

typedef const BLFsmMsg *PCBLFsmMsg;

typedef enum {
	BLFsmResult_Ignored,
	BLFsmResult_Handled,
	BLFsmResult_Transited
} BLFsmResult;

struct _BLFsm;

typedef void(*BLFsmActionHandler)(struct _BLFsm* fsm, PBLFsmMsg msg);
typedef BLFsmResult(*BLFsmStateHandler)(struct _BLFsm* fsm, PBLFsmMsg msg);
typedef struct _BLFsmState{
	const BLFsmStateHandler sh;
	const BLFsmActionHandler ahEnter, ahExit;
} BLFsmState, *PBLFsmState;
typedef const BLFsmState *PCBLFsmState;

typedef struct _BLFsm {
	const void* context;
	PBLFsmMsg msg;
	PCBLFsmState state;
} BLFsm, *PBLFsm;

#if defined(__cplusplus)
extern "C" {
#endif
	/*!
	\brief Initialize global and/or static variables of BLFsm.
	*/
	void BLFsm_SInit();
	void BLFsm_SUnInit();

	/*!
	\brief The default action handler does nothing.
	*/
	void AHNone(PBLFsm fsm, PBLFsmMsg msg);

	/*!
	\brief The default state handler does nothing.
	*/
	BLFsmResult SHNone(PBLFsm fsm, PBLFsmMsg msg);

	/*!
	\brief Main controller of transition of the state machine.
	*/
	BLFsmResult BLFsm_Transit(PBLFsm fsm, PBLFsm msg);

	/*!
	\brief Create a new object of BLFsmMsg
	*/
	PBLFsmMsg BLFsmMsg_New(int msg, BLTypes t, size_t cUnit);

	/*!
	\brief Increment references to the message object
	*/
	int BLFsmMsg_AddRef(PBLFsmMsg msg);

	/*!
	\brief Decrement references to the message object
	*/
	int BLFsmMsg_SubRef(PBLFsmMsg *ppmsg);
#if defined(__cplusplus)
}
#endif
