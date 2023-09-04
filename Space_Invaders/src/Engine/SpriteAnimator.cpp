#include "SpriteAnimator.h"
#include "Log.h"

namespace SpaceInvaders
{
    SpriteAnimator::SpriteAnimator()
    {

    }

    SpriteAnimator::~SpriteAnimator()
    {

    }

    void SpriteAnimator::CreateAnimation(std::string name, int (*condition)(int), int durationMs, int priority)
    {
        m_Animations[name] = condition;
        m_AnimationNames.push_back(name);
        m_AnimationDuration[name] = durationMs == 0 ? 99999 : durationMs;
        m_AnimationTimers[name] = m_AnimationDuration[name];
        m_Priority[name] = priority;
    }

    void SpriteAnimator::Animate(std::string name)
    {
        for (std::string n : m_AnimationNames)
        {
            if (m_AnimationTimers[n] != (float)m_AnimationDuration[n])
            {
                if (m_Priority[n] < m_Priority[name])
                    return;
            }
        }
        auto condition = m_Animations[name];
        m_ActiveSprite = condition(m_ActiveSprite);
        m_AnimationTimers[name] = (float)m_AnimationDuration[name] - 0.001f;
    }

    std::vector<std::string> SpriteAnimator::UpdateAnimationTimers(float ts)
    {
        std::vector<std::string> expired;
        for (std::string name : m_AnimationNames)
        {
            if (m_AnimationTimers[name] == (float)m_AnimationDuration[name]) continue;
            m_AnimationTimers[name] -= ts * 1000;
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
