#include "Alien.h"
#include "SpriteData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Alien::Alien(glm::vec2 size)
        : Actor(size)
    {
        m_Laser = new Laser(&m_Position, glm::vec2(0.0f, 1.0f),
            Sprite(BinaryTexture::Create(SpriteData::Projectile0, SpriteData::LayoutProjectile0)), glm::vec2(2.0f, 20.0f));
    }

    Alien::~Alien()
    {
        delete m_Laser;
    }

    void Alien::TakeDamage()
    {
        m_IsAlive = false;
    }

    Sprite& Alien::GetSprite(int animationTime)
    {
        if (animationTime % 2000 <= 1000)
            return m_Sprites[0];
        else
            return m_Sprites[1];
    }
}
