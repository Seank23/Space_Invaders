#include "Laser.h"
#include "SpriteData.h"

namespace SpaceInvaders
{
    Laser::Laser(int type, glm::vec2* position, glm::vec2 direction)
		: m_Direction(direction), m_ProjectileSpeed(200.0f)
	{
        m_Position = position;
        switch (type)
        {
        case 0:
            m_ProjectileSprites[0] = Sprite(BinaryTexture::Create(SpriteData::ProjectileExplosionSprite0, SpriteData::LayoutProjectileExplosionSprite0),
                { SpriteData::SizeProjectileExplosionSprite0[0], SpriteData::SizeProjectileExplosionSprite0[1] });
            m_ProjectileSprites[1] = Sprite(BinaryTexture::Create(SpriteData::Projectile0, SpriteData::LayoutProjectile0), glm::vec2(2.0f, 12.0f));
            break;
        case 1:
            m_ProjectileSprites[0] = Sprite(BinaryTexture::Create(SpriteData::ProjectileExplosionSprite1, SpriteData::LayoutProjectileExplosionSprite1),
                { SpriteData::SizeProjectileExplosionSprite1[0], SpriteData::SizeProjectileExplosionSprite1[1] });
            m_ProjectileSprites[1] = Sprite(BinaryTexture::Create(SpriteData::Projectile1, SpriteData::LayoutProjectile1), glm::vec2(6.0f, 18.0f));
            break;
        }
	}

	Laser::~Laser()
	{

	}

    void Laser::Shoot(float distanceToLive)
    {
        Projectile projectile = Projectile(m_ProjectileSpeed);
        for(int i = 0; i < m_ProjectileSprites.size(); i++)
            projectile.AddSprite(i, m_ProjectileSprites[i]);
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
