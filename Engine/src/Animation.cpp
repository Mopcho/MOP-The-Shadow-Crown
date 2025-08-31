#include "mopengine/Animation.hpp"

#include <functional>
#include <string>
#include <vector>

#include "raylib.h"
#include "mopengine/Constants.hpp"

Animation::Animation(const std::string& texturePath, const unsigned int parts, const int frameSpeed, const bool looping):
    m_texturePath(texturePath),
    m_texture(LoadTexture(texturePath.c_str())),
    m_spriteParts(parts),
    m_rect({0, 0, frameWidth(), frameHeight()}),
    m_frameSpeed(frameSpeed),
    m_looping(looping)
{
}

Animation::~Animation()
{
    UnloadTexture(m_texture);
}

[[nodiscard]] float Animation::frameWidth() const
{
    return static_cast<float>(m_texture.width) / static_cast<float>(m_spriteParts);
}

[[nodiscard]] float Animation::frameHeight() const
{
    return static_cast<float>(m_texture.height);
}

void Animation::FinishAnimation()
{
    m_isFinished = true;
    for (auto const& animationFinishEvent : m_onAnimationFinishedEvents)
    {
        animationFinishEvent();
    }
}

void Animation::RepeatAnimation()
{
    m_currentFrame = 0;
    m_isFinished = false;
}

void Animation::Process()
{
    if (m_isFinished == true)
    {
        return;
    }

    m_frameCounter++;
    if (m_frameCounter >= (FPS / m_frameSpeed))
    {
        m_frameCounter = 0;
        m_currentFrame++;

        if (m_currentFrame >= m_spriteParts)
        {
            if (m_looping)
            {
                RepeatAnimation();
            }
            else
            {
                FinishAnimation();
            }
        }

        m_rect.x = static_cast<float>(m_currentFrame) * frameWidth();
    }
}

void Animation::OnAnimationFinish(const std::function<void()>& callback)
{
    m_onAnimationFinishedEvents.emplace_back(callback);
}
