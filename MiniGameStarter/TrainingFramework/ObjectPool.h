#pragma once
class MainCharacter;
template <class T>
class ObjectPool
{
private:
    std::list<T*> resources;

    static ObjectPool* instance;
    ObjectPool() {}

public:
    static ObjectPool* getInstance()
    {
        if (instance == 0)
        {
            instance = new ObjectPool;
        }
        return instance;
    }
    T* getResource()
    {
        if (resources.empty())
        {
            return new T();
        }
        else
        {
            T* resource = resources.front();
            resources.pop_front();
            return resource;
        }
    }
    T* getResource2(Vector3 position)
    {
        std::cout << resources.size();
        if (resources.empty())
        {
            std::cout << "Creating new." << std::endl;
            return new T(position);
        }
        else
        {
            std::cout << "Reusing existing." << std::endl;
            T* resource = resources.front();
            resource->Set2DPosition(Vector2(position.x,position.y));
            resources.pop_front();
            return resource;
        }
    }
    void returnResource(T* object)
    {
        object->Reset();
        resources.push_back(object);
    }
};