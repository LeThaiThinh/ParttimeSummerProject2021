#pragma once
class DoorContext;
class DoorStateBase
{
public :
    DoorStateBase();
    virtual void openDoor(DoorContext* doorContext)=0;
    virtual void lockDoor(DoorContext* doorContext)=0;
    virtual void closeDoor(DoorContext* doorContext)=0;
    virtual void unlockDoor(DoorContext* doorContext)=0;

};

