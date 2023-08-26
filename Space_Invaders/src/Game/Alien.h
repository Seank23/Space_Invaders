#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Engine/SpriteRenderer.h"

#include <memory>
#include <vector>

namespace SpaceInvaders
{
	class Alien : public Actor
	{
	public:
		Alien(glm::vec2 size);
		~Alien();

		void Shoot(float distanceToLive);
		void CullProjectiles();

		virtual void SetSprite(Sprite& sprite) override { m_Sprites.push_back(sprite); }
		Sprite& GetSprite(int animationTime);

		std::vector<std::shared_ptr<Projectile>> GetProjectiles() { return m_Projectiles; }
		glm::vec2 GetShootDirection() { return m_ShootDirection; }
		float GetShootChance() { return m_ShootChance; }

	private:
		std::vector<Sprite> m_Sprites;
		std::vector<std::shared_ptr<Projectile>> m_Projectiles;
		std::shared_ptr<Sprite> m_ProjectileSprite;
		glm::vec2 m_ShootDirection;
		float m_ShootChance = 0.00025;
	};
}

