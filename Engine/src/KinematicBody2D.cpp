#include "mopengine/KinematicBody2D.hpp"

#include <iostream>

KinematicBody2D::KinematicBody2D(Vector2 pos): m_pos(pos)
{
}

KinematicBody2D::~KinematicBody2D() = default;

void KinematicBody2D::setScaleSize(Vector2 scale)
{
    m_scaleSize.x = scale.x;
    m_scaleSize.y = scale.y;
}

void KinematicBody2D::SetAnimationPlayer(AnimationPlayer&& animationPlayer)
{
    m_animationPlayer = animationPlayer;
}

void KinematicBody2D::Move(Vector2 moveWith)
{
    m_pos.x += moveWith.x;
    m_pos.y += moveWith.y;
}

void KinematicBody2D::Process()
{
    m_animationPlayer.Process();
    auto animation = m_animationPlayer.GetCurrentAnimation();
    processFlipH();
    m_dest = {m_pos.x, m_pos.y, animation->frameWidth() * m_scaleSize.x, animation->frameHeight() * m_scaleSize.y};
    m_origin = {animation->frameWidth(), animation->frameHeight()};
}

void KinematicBody2D::Draw()
{
    auto animation = m_animationPlayer.GetCurrentAnimation();
    DrawTexturePro(animation->m_texture, animation->m_rect, m_dest, m_origin, 0.0f, WHITE);
}

void KinematicBody2D::processFlipH() const
{
    // TODO: Check this
    auto animation = m_animationPlayer.GetCurrentAnimation();
    if (m_flipH && animation->m_rect.width > 0)
    {
        animation->m_rect.width = animation->m_rect.width * -1;
    }
    else if (!m_flipH && animation->m_rect.width < 0)
    {
        animation->m_rect.width = animation->m_rect.width * -1;
    }
}

AnimationPlayer KinematicBody2D::GetAnimationPlayer() const
{
    return m_animationPlayer;
}
