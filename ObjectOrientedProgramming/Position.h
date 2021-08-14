#pragma once
#include <iostream>
class Position {
private:
    float x;
    float y;
public:
    Position();
    Position(float x, float y);
    ~Position();
    void printPosition();
    void move(float x, float y);
};