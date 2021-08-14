#include "House.h"
House::House(){}

House::House(int id, std::string name, Position position) :StaticObject(id, name, position) {}

House::~House(){}
