#ifndef RIGIDBODY2D_HPP
#define RIGIDBODY2D_HPP

#include <functional>

#include "SpriteModule.hpp"

class RigidBody2D
{
public:
    Vector2 m_pos;
    SpriteModule * m_spriteModule;
    bool m_flipH = false;

    RigidBody2D(Vector2 pos, SpriteModule * spriteModule): m_pos(pos), m_spriteModule(spriteModule)
    {
        initializeEvents();
    }

    ~RigidBody2D()
    {
    }

    void setSpriteModule(SpriteModule * newSpriteModule)
    {
        m_spriteModule = newSpriteModule;
    }

    void Update()
    {
        // Adjust to m_flipH
        if (m_flipH && m_spriteModule->m_rect.width > 0)
        {
            m_spriteModule->m_rect.width = m_spriteModule->m_rect.width * -1;
        } else if (!m_flipH && m_spriteModule->m_rect.width < 0)
        {
            m_spriteModule->m_rect.width = m_spriteModule->m_rect.width * -1;
        }

        detectMovement(); // Replcae with smth else
        m_spriteModule->Update();
        Rectangle dest = {m_pos.x, m_pos.y, m_spriteModule->frameWidth()*2.0f, m_spriteModule->frameHeight()*2.0f};
        Vector2 origin = {m_spriteModule->frameWidth(), m_spriteModule->frameHeight()};
        DrawTexturePro(m_spriteModule->m_texture, m_spriteModule->m_rect, dest, origin, 0.0f , WHITE);
    }

    void On(const std::string & eventName, const std::function<void()>& func)
    {
        m_callbacksRegister.at(eventName).emplace_back(func);
    }

private:
    Vector2 m_previousPosition;
    std::unordered_map<std::string, std::vector<std::function<void()>>> m_callbacksRegister;

    void detectMovement()
    {
        if (m_previousPosition.x != m_pos.x || m_previousPosition.y != m_pos.y)
        {
            for (auto const & cb : m_callbacksRegister.at("run"))
            {
                cb();
            }
        } else
        {
            for (auto const & cb : m_callbacksRegister.at("idle"))
            {
                cb();
            }
        }
        m_previousPosition = m_pos;
    }

    void initializeEvents()
    {
        m_callbacksRegister["run"] = {};
        m_callbacksRegister["idle"] = {};
    }
    
};

#endif //RIGIDBODY2D_HPP
