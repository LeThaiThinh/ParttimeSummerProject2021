#include "DoorContext.h"
#include <iostream>


DoorContext::DoorContext(DoorStateBase* pDoorState) :m_pDoorState(pDoorState){}

DoorContext::~DoorContext()
{
	delete m_pDoorState;
	m_pDoorState = nullptr;
}

void DoorContext::openDoor()
{
	if (m_pDoorState) {
		std::cout << "Open door" << std::endl;
		m_pDoorState->openDoor(this);
	}
}

void DoorContext::closeDoor()
{
	if (m_pDoorState) {
		std::cout << "Close door" << std::endl;
		m_pDoorState->closeDoor(this);
	}
}

void DoorContext::lockDoor()
{
	if (m_pDoorState ) {
		std::cout << "Lock door" << std::endl;
		m_pDoorState->lockDoor(this);
	}
}


void DoorContext::unlockDoor()
{
	if (m_pDoorState) {
		std::cout << "Unlock door" << std::endl;
		m_pDoorState->unlockDoor(this);
	}
}

void DoorContext::setState(State state)
{
	switch (state)
	{
	case OPENED:
		m_pDoorState = new DoorOpenedState();
		break;
	case CLOSED:
		m_pDoorState = new DoorClosedState();
		break;
	case LOCKED:
		m_pDoorState = new DoorLockedState();
		break;
	default:
		break;
	}
}

DoorStateBase* DoorContext::getState()
{
	return m_pDoorState;
}
