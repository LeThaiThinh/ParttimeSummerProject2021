#pragma once
#include "DynamicObject.h"
class Motobike :public DynamicObject {
public:
    Motobike();
    Motobike(int id, std::string name, Position position) ;
    ~Motobike();
};
