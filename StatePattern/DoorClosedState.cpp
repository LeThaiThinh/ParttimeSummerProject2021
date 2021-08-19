#include "DoorClosedState.h"
#include <iostream>


DoorClosedState::DoorClosedState() 
{
    std::cout << "Door is closed" << std::endl;
}

void DoorClosedState::openDoor(DoorContext* doorContext)
{
    doorContext->setState(DoorContext::OPENED);
}

void DoorClosedState::closeDoor(DoorContext*  doorContext)
{
    std::cout << "Door is still closed" << std::endl;
}

void DoorClosedState::lockDoor(DoorContext* doorContext)
{
    doorContext->setState(DoorContext::LOCKED);
}
 
void DoorClosedState::unlockDoor(DoorContext* doorContext)
{
    std::cout << "Door is still closed" << std::endl;
}
