#include "BaseObject.h"
BaseObject::BaseObject() {
    this->id = 0;
    this->name = "Noname";
    this->position = Position(0,0);
};
BaseObject::~BaseObject() {};
BaseObject::BaseObject(int id,std::string name, Position position) {
    this->id = id;
    this->name = name;
    this->position = position;
};
int BaseObject::getId() { return this->id; }
void BaseObject::setId(int id) { this->id = id; }
std::string BaseObject::getName() { return name; }
void BaseObject::setName(std::string name) { this->name = name; }
Position BaseObject::getPosition() { return this->position; }
void BaseObject::move(Position position) { this->position = position; }
void BaseObject::move(float x, float y) { this->position.move(x, y); }
void BaseObject::printPosition() { this->position.printPosition(); }