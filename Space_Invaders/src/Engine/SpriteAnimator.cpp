#include "SpriteAnimator.h"

namespace SpaceInvaders
{
    SpriteAnimator::SpriteAnimator()
    {

    }

    SpriteAnimator::~SpriteAnimator()
    {

    }

    void SpriteAnimator::CreateAnimation(std::string name, int(*condition)(int))
    {
        m_Animations[name] = condition;
    }

    void SpriteAnimator::Animate(std::string name)
    {
        auto condition = m_Animations[name];
        m_ActiveSprite = condition(m_ActiveSprite);
    }

    void SpriteAnimator::AddSprite(int id, Sprite& sprite)
    {
        m_Sprites[id] = sprite;
    }
}
