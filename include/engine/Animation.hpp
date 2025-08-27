#ifndef SPRITEMODULE_HPP
#define SPRITEMODULE_HPP

#include "Constants.hpp"
#include "raylib.h"

class Animation
{
public:
    Texture2D m_texture;
    unsigned int m_spriteParts;
    Rectangle m_rect;
    int m_frameSpeed;
    unsigned int m_frameCounter = 0;
    unsigned int m_currentFrame = 0;
    bool m_looping;
    bool m_isFinished = false;

    Animation(const char* texturePath, unsigned int parts, int frameSpeed = 8, bool looping = true):
        m_texture(LoadTexture(texturePath)),
        m_spriteParts(parts),
        m_rect(0, 0, frameWidth(), frameHeight()),
        m_frameSpeed(frameSpeed),
        m_looping(looping)
    {
    }

    ~Animation()
    {
        UnloadTexture(m_texture);
    }

    void OnAnimationFinish(const std::function<void()>& cb)
    {
        m_onAnimationFinishedEvents.emplace_back(cb);
    }

    float frameWidth()
    {
        return (float)m_texture.width/m_spriteParts;
    }

    float frameHeight()
    {
        return (float)m_texture.height;
    }

    void FinishAnimation()
    {
        m_isFinished = true;
        for (auto const & animationFinishEvent : m_onAnimationFinishedEvents)
        {
            animationFinishEvent();
        }
    }

    void RepeatAnimation()
    {
        m_currentFrame = 0;
        m_isFinished = false;
    }

    void Process()
    {
        if (m_isFinished == true)
        {
            return;
        }

        m_frameCounter++;
        if (m_frameCounter >= (FPS/m_frameSpeed))
        {
            m_frameCounter = 0;
            m_currentFrame++;

            if (m_currentFrame > m_spriteParts)
            {
                if (m_looping)
                {
                    RepeatAnimation();
                } else
                {
                    FinishAnimation();
                }
            }

            m_rect.x = (float)m_currentFrame * frameWidth();
        }
    }

private:
    std::vector<std::function<void()>> m_onAnimationFinishedEvents {};
};

#endif //SPRITEMODULE_HPP