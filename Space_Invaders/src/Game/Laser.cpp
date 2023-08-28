#include "Laser.h"
#include "SpriteData.h"

namespace SpaceInvaders
{
    Laser::Laser(glm::vec2* position, glm::vec2 direction, Sprite& projectileSprite, glm::vec2 projectileSize)
		: m_Direction(direction), m_ProjectileSize(projectileSize), m_ProjectileSpeed(200.0f)
	{
		m_ProjectileSprite = projectileSprite;
        m_Position = position;
	}

	Laser::~Laser()
	{

	}

    void Laser::Shoot(float distanceToLive)
    {
        Projectile projectile = Projectile(m_ProjectileSize, m_ProjectileSpeed);
        projectile.SetSprite(m_ProjectileSprite);
        projectile.SetPosition(*m_Position);
        projectile.SetDistanceToLive(distanceToLive);
        m_Projectiles.push_back(projectile);
    }

    void Laser::CullProjectiles()
    {
        m_Projectiles.erase(
            std::remove_if(
                m_Projectiles.begin(),
                m_Projectiles.end(),
                [](Projectile& p) { return p.GetDistanceToLive() <= 0; }
            ),
            m_Projectiles.end()
        );
    }
}
