#include "DoorOpenedState.h"
#include <iostream>


DoorOpenedState::DoorOpenedState() 
{
    std::cout << "Door is opened" << std::endl;
}

void DoorOpenedState::openDoor(DoorContext* doorContext)
{
    std::cout << "Door is still opened" << std::endl;
}

void DoorOpenedState::closeDoor(DoorContext* doorContext)
{
    doorContext->setState(DoorContext::CLOSED);
}

void DoorOpenedState::lockDoor(DoorContext* doorContext)
{
    std::cout << "Door is still opened" << std::endl;
}

void DoorOpenedState::unlockDoor(DoorContext* doorContext)
{
    std::cout << "Door is still opened" << std::endl;
}