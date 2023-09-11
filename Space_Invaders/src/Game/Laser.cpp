#include "Laser.h"
#include "SpriteData.h"

namespace SpaceInvaders
{
    Laser::Laser(int type, glm::vec2* position, glm::vec2 direction)
		: m_Direction(direction), m_ProjectileSpeed(200.0f), m_StateManager(GameStateManager::Instance())
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
            m_ProjectileSprites[1] = Sprite(BinaryTexture::Create(SpriteData::Projectile2, SpriteData::LayoutProjectile2), glm::vec2(8.0f, 20.0f));
            break;
        }
	}

	Laser::~Laser()
	{

	}

    void Laser::Shoot(float distanceToLive)
    {
        std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(m_ProjectileSpeed, m_Direction);
        for(int i = 0; i < m_ProjectileSprites.size(); i++)
            projectile->AddSprite(i, m_ProjectileSprites[i]);
        projectile->SetPosition(*m_Position);
        projectile->SetDistanceToLive(distanceToLive);
        m_StateManager->AddProjectile(projectile);
    }
}
