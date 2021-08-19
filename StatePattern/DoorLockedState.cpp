#include "DoorLockedState.h"
#include <iostream>


DoorLockedState::DoorLockedState() 
{
    std::cout << "Door is locked" << std::endl;
}

void DoorLockedState::openDoor(DoorContext* doorContext)
{
    std::cout << "Door is still locked" << std::endl;
}

void DoorLockedState::closeDoor(DoorContext* doorContext)
{
    std::cout << "Door is still locked" << std::endl;
}

void DoorLockedState::lockDoor(DoorContext* doorContext)
{
    std::cout << "Door is still locked" << std::endl;
}

void DoorLockedState::unlockDoor(DoorContext* doorContext)
{
    doorContext->setState(DoorContext::CLOSED);
}
