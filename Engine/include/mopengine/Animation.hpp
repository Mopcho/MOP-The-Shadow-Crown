#ifndef SPRITEMODULE_HPP
#define SPRITEMODULE_HPP

#include <functional>
#include <string>
#include <vector>

#include "Constants.hpp"
#include "raylib.h"

class Animation
{
public:
    std::string m_texturePath;
    Texture2D m_texture;
    unsigned int m_spriteParts;
    Rectangle m_rect;
    int m_frameSpeed;
    bool m_looping;
    bool m_isFinished = false;
    unsigned int m_frameCounter = 0;
    unsigned int m_currentFrame = 0;

    MOPENGINE_API Animation(const std::string& texturePath, unsigned int parts, int frameSpeed = 8, bool looping = true);
    MOPENGINE_API ~Animation();
    MOPENGINE_API void OnAnimationFinish(const std::function<void()>& callback);
    MOPENGINE_API [[nodiscard]] float frameWidth() const;
    MOPENGINE_API [[nodiscard]] float frameHeight() const;
    MOPENGINE_API void FinishAnimation();
    MOPENGINE_API void RepeatAnimation();
    MOPENGINE_API void Process();

private:
    std::vector<std::function<void()>> m_onAnimationFinishedEvents {};
};

#endif //SPRITEMODULE_HPP