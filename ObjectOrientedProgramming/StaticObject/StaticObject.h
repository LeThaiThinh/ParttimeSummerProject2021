#pragma once
#include "../BaseObject.h"
class StaticObject : public BaseObject
{
public:
    StaticObject();
    StaticObject(int id, std::string name, Position position);
    ~StaticObject();
    void move(Position position);
    void move(float x, float y);
};