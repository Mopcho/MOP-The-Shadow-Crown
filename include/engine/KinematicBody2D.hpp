#ifndef RIGIDBODY2D_HPP
#define RIGIDBODY2D_HPP

#include <functional>

#include "GameObject.hpp"
#include "SpriteModule.hpp"

class KinematicBody2D : public GameObject
{
public:
    Vector2 m_pos;
    Vector2 m_scaleSize = { 1.0f, 1.0f };
    std::string m_selectedSpriteModule;
    bool m_flipH = false;
    std::unordered_map<std::string, SpriteModule *> m_spriteModules = {};

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

    void AddSpriteModule(const std::string & name, SpriteModule * spriteModule)
    {
        m_spriteModules[name] = spriteModule;
    }

    void SetPlaySpriteModule(const std::string & name)
    {
        m_selectedSpriteModule = name;
    }

    SpriteModule* GetCurrentSpriteModule()
    {
        return m_spriteModules.at(m_selectedSpriteModule);
    }

    void Move(Vector2 moveWith)
    {
        m_pos.x += moveWith.x;
        m_pos.y += moveWith.y;
    }

    void Draw()
    {
        auto spriteModule = GetCurrentSpriteModule();
        processFlipH();

        spriteModule->Update();
        Rectangle dest = {m_pos.x, m_pos.y, spriteModule->frameWidth()*m_scaleSize.x, spriteModule->frameHeight()*m_scaleSize.y};
        Vector2 origin = {spriteModule->frameWidth(), spriteModule->frameHeight()};
        DrawTexturePro(spriteModule->m_texture, spriteModule->m_rect, dest, origin, 0.0f , WHITE);
    }

private:
    Vector2 m_previousPosition;
    void processFlipH()
    {
        auto spriteModule = GetCurrentSpriteModule();
        if (m_flipH && spriteModule->m_rect.width > 0)
        {
            spriteModule->m_rect.width = spriteModule->m_rect.width * -1;
        } else if (!m_flipH && spriteModule->m_rect.width < 0)
        {
            spriteModule->m_rect.width = spriteModule->m_rect.width * -1;
        }
    }
};

#endif //RIGIDBODY2D_HPP
