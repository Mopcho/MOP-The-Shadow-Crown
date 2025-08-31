#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <mopengine/KinematicBody2D.hpp>

class Player : public KinematicBody2D
{
public:
    Player(Vector2 pos): KinematicBody2D(pos)
    {
    }
};

#endif //PLAYER_HPP
