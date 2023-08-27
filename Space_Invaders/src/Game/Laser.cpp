#include "Laser.h"
#include "SpriteData.h"

namespace SpaceInvaders
{
	Laser::Laser(glm::vec2* position, glm::vec2 direction, std::shared_ptr<Sprite> projectileSprite, glm::vec2 projectileSize)
		: m_Position(position), m_Direction(direction), m_ProjectileSize(projectileSize)
	{
		m_ProjectileSprite = projectileSprite;
	}

	Laser::~Laser()
	{

	}

    void Laser::Shoot(float distanceToLive)
    {
        std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(m_ProjectileSize);
        projectile->SetSprite(*m_ProjectileSprite);
        projectile->SetPosition(*m_Position);
        projectile->SetDistanceToLive(distanceToLive);
        m_Projectiles.push_back(projectile);
    }

    void Laser::CullProjectiles()
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
