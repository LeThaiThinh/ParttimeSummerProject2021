#pragma once
#include "./Position.h"
class BaseObject {
private:
    int id;
    std::string name;
    Position position;
public:
    BaseObject();
    BaseObject(int id, std::string name, Position position);
    ~BaseObject();

    int getId();
    void setId(int id);

    std::string getName();
    void setName(std::string name);

    Position getPosition();
    virtual void move(Position position);
    virtual void move(float x, float y);
    void printPosition();

};