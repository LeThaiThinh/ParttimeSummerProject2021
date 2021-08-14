#pragma once
#include "DynamicObject.h"
class Car :public DynamicObject {
public:
    Car();
    Car(int id, std::string name, Position position);
    ~Car();

};