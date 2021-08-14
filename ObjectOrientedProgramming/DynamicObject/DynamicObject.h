#pragma once
#include "../BaseObject.h"
class DynamicObject :public BaseObject{
public:
    DynamicObject();
    DynamicObject(int id, std::string name, Position position);
    ~DynamicObject();
};