#include "Car.h"

Car::Car(){}

Car::Car(int id, std::string name, Position position) :DynamicObject(id, name, position) {}

Car::~Car(){}
