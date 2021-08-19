#pragma once
#include "DoorOpenedState.h"
#include "DoorClosedState.h"
#include "DoorLockedState.h"
#include <string>
#include "DoorStateBase.h"

class DoorContext
{
public:

	DoorContext(DoorStateBase* pDoorState);
	~DoorContext();

	enum State
	{
		CLOSED,
		LOCKED,
		OPENED
	};

	void openDoor();
	void closeDoor();
	void lockDoor();
	void unlockDoor();
	void setState(State state);
	DoorStateBase* getState();
private:
	DoorStateBase* m_pDoorState;
};

