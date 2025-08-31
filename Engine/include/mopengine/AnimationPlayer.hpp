#ifndef ANIMATIONPLAYER_HPP
#define ANIMATIONPLAYER_HPP

#include "Animation.hpp"
#include "Constants.hpp"

class AnimationPlayerImpl;

class MOPENGINE_API AnimationPlayer
{
public:
    AnimationPlayer();
    ~AnimationPlayer();

    void AddAnimation(const std::string & name, Animation* animation);
    void PlayAnimation(const std::string & name);
    void PlayAnimationWhenReady(const std::string & name);
    [[nodiscard]] Animation* GetCurrentAnimation() const;
    void Process() const;

private:
    std::string m_selectedAnimation;
    std::unordered_map<std::string, Animation*> m_animations = {};
};
#endif //ANIMATIONPLAYER_HPP
