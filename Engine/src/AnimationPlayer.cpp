#include "mopengine/AnimationPlayer.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

AnimationPlayer::AnimationPlayer() = default;
AnimationPlayer::~AnimationPlayer() = default;

void AnimationPlayer::AddAnimation(const std::string& name, Animation* animation)
{
    m_animations[name] = animation;
}

void AnimationPlayer::PlayAnimation(const std::string& name)
{
    m_selectedAnimation = name;
    auto animation = GetCurrentAnimation();
    if (!animation->m_looping)
    {
        animation->m_isFinished = false;
        animation->m_currentFrame = 0;
    }
}

void AnimationPlayer::PlayAnimationWhenReady(const std::string& name)
{
    auto animation = GetCurrentAnimation();
    if (animation->m_looping)
    {
        this->PlayAnimation(name);
    }
    else
    {
        animation->OnAnimationFinish([this, name]()
        {
            this->PlayAnimation(name);
        });
    }
}

[[nodiscard]] Animation* AnimationPlayer::GetCurrentAnimation() const
{
    return m_animations.at(m_selectedAnimation);
}

void AnimationPlayer::Process() const
{
    GetCurrentAnimation()->Process();
}

