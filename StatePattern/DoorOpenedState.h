#pragma once
#include "DoorContext.h"
#include "DoorStateBase.h"
class DoorOpenedState :
    public DoorStateBase
{
public:
    DoorOpenedState();
    virtual void openDoor(DoorContext* doorContext);
    virtual void lockDoor(DoorContext* doorContext);
    virtual void closeDoor(DoorContext* doorContext);
    virtual void unlockDoor(DoorContext* doorContext);

};

