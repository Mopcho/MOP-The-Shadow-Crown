#ifndef RIGIDBODY2D_HPP
#define RIGIDBODY2D_HPP

#include <functional>

#include "GameObject.hpp"
#include "Animation.hpp"

class KinematicBody2D : public GameObject
{
public:
    Vector2 m_pos;
    Vector2 m_scaleSize = { 1.0f, 1.0f };
    std::string m_selectedAnimation;
    bool m_flipH = false;
    std::unordered_map<std::string, Animation *> m_animations = {};

    KinematicBody2D(Vector2 pos): m_pos(pos)
    {
    }

    ~KinematicBody2D()
    {
    }

    void setScaleSize(Vector2 scale)
    {
        m_scaleSize.x = scale.x;
        m_scaleSize.y = scale.y;
    }

    void AddAnimation(const std::string & name, Animation * spriteModule)
    {
        m_animations[name] = spriteModule;
    }

    void PlayAnimation(const std::string & name)
    {
        m_selectedAnimation = name;
        auto animation = GetCurrentAnimation();
        if (!animation->m_looping)
        {
            animation->m_isFinished = false;
            animation->m_currentFrame = 0;
        }
    }

    void PlayAnimationWhenReady(const std::string & name)
    {
        auto animation = GetCurrentAnimation();
        if (animation->m_looping)
        {
            this->PlayAnimation(name);
        } else
        {
            animation->OnAnimationFinish([this, name]()
            {
                this->PlayAnimation(name);
            });
        }
    }

    Animation* GetCurrentAnimation()
    {
        return m_animations.at(m_selectedAnimation);
    }

    void Move(Vector2 moveWith)
    {
        m_pos.x += moveWith.x;
        m_pos.y += moveWith.y;
    }

    void Process()
    {
        auto animation = GetCurrentAnimation();
        animation->Process();
        processFlipH();
        m_dest = {m_pos.x, m_pos.y, animation->frameWidth()*m_scaleSize.x, animation->frameHeight()*m_scaleSize.y};
        m_origin = {animation->frameWidth(), animation->frameHeight()};
    }

    void Draw()
    {
        auto animation = GetCurrentAnimation();
        DrawTexturePro(animation->m_texture, animation->m_rect, m_dest, m_origin, 0.0f , WHITE);
    }

private:
    Rectangle m_dest;
    Vector2 m_origin;

    void processFlipH()
    {
        auto animation = GetCurrentAnimation();
        if (m_flipH && animation->m_rect.width > 0)
        {
            animation->m_rect.width = animation->m_rect.width * -1;
        } else if (!m_flipH && animation->m_rect.width < 0)
        {
            animation->m_rect.width = animation->m_rect.width * -1;
        }
    }
};

#endif //RIGIDBODY2D_HPP
