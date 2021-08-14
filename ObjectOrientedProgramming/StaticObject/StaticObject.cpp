#include "StaticObject.h"

StaticObject::StaticObject(){}

StaticObject::StaticObject(int id, std::string name, Position position) :BaseObject(id, name, position) {}

StaticObject::~StaticObject(){}

void StaticObject::move(Position position)
{
	std::cout << "It's static ,cant move" << std::endl;
}

void StaticObject::move(float x, float y)
{
	std::cout << "It's static ,cant move" << std::endl;
}
