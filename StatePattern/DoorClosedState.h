#pragma once
#include "DoorContext.h"
#include "DoorStateBase.h"
class DoorClosedState :
    public DoorStateBase
{
public:
    DoorClosedState();
    virtual void openDoor(DoorContext* doorContext);
    virtual void lockDoor(DoorContext* doorContext);
    virtual void closeDoor(DoorContext* doorContext);
    virtual void unlockDoor(DoorContext* doorContext);

};

