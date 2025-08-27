#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject
{
public:
    virtual ~GameObject() = default;
    virtual void Draw() = 0;
};

#endif //GAMEOBJECT_HPP
