#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "raylib.h"

class CollisionRectangle
{
public:
    Rectangle m_rect;
    CollisionRectangle(Rectangle rect) : m_rect(rect)
    {

    }
};

#endif //COLLISION_HPP
