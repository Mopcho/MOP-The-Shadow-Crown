#ifndef RIGIDBODY2D_HPP
#define RIGIDBODY2D_HPP

#include "Drawable.hpp"
#include "AnimationPlayer.hpp"
#include "raylib.h"

class KinematicBody2DImpl;

class MOPENGINE_API KinematicBody2D : public Drawable
{
public:
    Vector2 m_pos;
    Vector2 m_scaleSize = {1.0f, 1.0f};
    bool m_flipH = false;
    AnimationPlayer m_animationPlayer;

    explicit KinematicBody2D(Vector2 pos);
    ~KinematicBody2D() override;
    void SetAnimationPlayer(AnimationPlayer&& animationPlayer);
    void setScaleSize(Vector2 scale);
    void Move(Vector2 moveWith);
    void Process() override;
    void Draw() override;
    [[nodiscard]] AnimationPlayer GetAnimationPlayer() const;

private:
    Rectangle m_dest;
    Vector2 m_origin;

    void processFlipH() const;
};

#endif //RIGIDBODY2D_HPP
