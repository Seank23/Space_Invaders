#include "SpriteAnimator.h"

namespace SpaceInvaders
{
    SpriteAnimator::SpriteAnimator()
    {

    }

    SpriteAnimator::~SpriteAnimator()
    {

    }

    void SpriteAnimator::CreateAnimation(std::string name, int(*condition)(int), int durationMs = 0)
    {
        m_Animations[name] = condition;
        m_AnimationNames.push_back(name);
        m_AnimationDuration[name] = durationMs == 0 ? 99999 : durationMs;
    }

    void SpriteAnimator::Animate(std::string name)
    {
        auto condition = m_Animations[name];
        m_ActiveSprite = condition(m_ActiveSprite);
        m_AnimationTimers[name] = m_AnimationDuration[name];
    }

    std::vector<std::string> SpriteAnimator::UpdateAnimationTimers(float timestep)
    {
        std::vector<std::string> expired;
        for (std::string name : m_AnimationNames)
        {
            m_AnimationTimers[name] -= ts;
            if (m_AnimationTimers[name] <= 0)
            {
                expired.push_back(name);
                m_AnimationTimers[name] = m_AnimationDuration[name];
            }
        }
        return expired;
    }

    void SpriteAnimator::AddSprite(int id, Sprite& sprite)
    {
        m_Sprites[id] = sprite;
    }
}
