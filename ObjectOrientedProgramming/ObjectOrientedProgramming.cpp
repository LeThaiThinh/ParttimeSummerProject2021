#include <list>
#include "DynamicObject/Car.h"
#include "StaticObject/Tree.h"
#include "DynamicObject/Motobike.h"
#include "StaticObject/House.h"
int main()
{
    std::list<BaseObject*> listObj= std::list<BaseObject*>();
    BaseObject* tree = new Tree(1, "Apple", Position(1, 1));
    BaseObject* house = new House(2, "White House", Position(2, 2));
    BaseObject* motobike = new Motobike(3, "SH", Position(3, 3));
    BaseObject* car = new Car(4, "Ford", Position(4, 4));

    listObj.push_back(tree);
    listObj.push_back(house);
    listObj.push_back(motobike);
    listObj.push_back(car);

    for (auto obj : listObj) {
        std::cout<<obj->getName()<<" ";
    }
    std::cout << std::endl;
    for (auto obj : listObj) {
        obj->move(2.5, 3.5);
    }   
    std::cout << std::endl;
    for (auto obj : listObj) {
        obj->printPosition();
    }
}
