#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Constants.hpp"

class MOPENGINE_API GameObject
{
public:
    virtual ~GameObject() = default;
    virtual void Draw() = 0;
    virtual void Process() = 0;
};

#endif //GAMEOBJECT_HPP
