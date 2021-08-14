#include "Position.h"

Position::Position(){
    this->x = 0;
    this->y = 0;
}

Position::Position(float x, float y)
{
    this->x = x;
    this->y = y;
}

Position::~Position(){}

void Position::printPosition()
{
   std::cout << "(" << this->x << ";" << this->y << ") ";
}

void Position::move(float x, float y)
{
    this->x += x; this->y += y;
}
