#include "Alien.h"
#include "SpriteData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Alien::Alien(glm::vec2 size)
        : Actor(size)
    {
        m_Laser = std::make_shared<Laser>(&m_Position, glm::vec2(0.0f, 1.0f),
            std::make_shared<Sprite>(BinaryTexture::Create(SpriteData::Projectile1, SpriteData::LayoutProjectile1)), glm::vec2(8.0f, 12.0f));
    }

    Alien::~Alien()
    {

    }

    Sprite& Alien::GetSprite(int animationTime)
    {
        if (animationTime % 2000 <= 1000)
            return m_Sprites[0];
        else
            return m_Sprites[1];
    }
}
