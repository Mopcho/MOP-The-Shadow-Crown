#ifndef SPRITEMODULE_HPP
#define SPRITEMODULE_HPP

#include "raylib.h"

class SpriteModule
{
public:
    Texture2D m_texture;
    unsigned int m_spriteParts;
    Rectangle m_rect;
    int m_frameSpeed;
    unsigned int m_frameCounter = 0;
    unsigned int m_currentFrame = 0;
    bool m_looping;
    bool m_automatic;

    const int FPS = 60; // TODO: Get this from the app instead

    SpriteModule(const char* texturePath, unsigned int parts, int frameSpeed = 8, bool looping = true, bool automatic = true):
        m_texture(LoadTexture(texturePath)),
        m_spriteParts(parts),
        m_rect(0, 0, frameWidth(), frameHeight()),
        m_frameSpeed(frameSpeed),
        m_looping(looping),
        m_automatic(automatic)
    {
    }

    ~SpriteModule()
    {
        UnloadTexture(m_texture);
    }

    float frameWidth()
    {
        return (float)m_texture.width/m_spriteParts;
    }

    float frameHeight()
    {
        return (float)m_texture.height;
    }

    void Update()
    {
        m_frameCounter++;
        if (m_frameCounter >= (FPS/m_frameSpeed))
        {
            m_frameCounter = 0;
            m_currentFrame++;

            if (m_currentFrame > m_spriteParts) m_currentFrame = 0;

            m_rect.x = (float)m_currentFrame * frameWidth();
        }
    }
};

#endif //SPRITEMODULE_HPP