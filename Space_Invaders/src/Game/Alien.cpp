#include "Alien.h"
#include "SpriteData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Alien::Alien(glm::vec2 size)
        : Actor(size), m_ShootDirection({ 0.0f, 1.0f })
    {
        m_ProjectileSprite = std::make_shared<Sprite>(BinaryTexture::Create(SpriteData::Projectile0, SpriteData::LayoutProjectile0, 0xFFFFFFFF));
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

    void Alien::Shoot(float distanceToLive)
    {
        std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(glm::vec2(2.0f, 8.0f));
        projectile->SetSprite(*m_ProjectileSprite);
        projectile->SetPosition(this->GetPosition());
        projectile->SetDistanceToLive(distanceToLive);
        m_Projectiles.push_back(projectile);
    }

    void Alien::CullProjectiles()
    {
        m_Projectiles.erase(
            std::remove_if(
                m_Projectiles.begin(),
                m_Projectiles.end(),
                [](std::shared_ptr<Projectile> p) { return p->GetDistanceToLive() <= 0; }
            ),
            m_Projectiles.end()
        );
    }
}
