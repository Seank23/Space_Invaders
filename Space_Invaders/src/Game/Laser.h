#pragma once
#include "Projectile.h"
#include <Engine/Sprite.h>

#include <memory>
#include <vector>

namespace SpaceInvaders
{
	class Laser
	{
	public:
		Laser(glm::vec2* position, glm::vec2 direction, Sprite& projectileSprite, glm::vec2 projectileSize);
		~Laser();

		void Shoot(float distanceToLive);
		void CullProjectiles();

		std::vector<Projectile>* GetProjectiles() { return &m_Projectiles; }
		glm::vec2 GetDirection() { return m_Direction; }
		void SetProjectileSpeed(float speed) { m_ProjectileSpeed = speed; }

	private:
		std::vector<Projectile> m_Projectiles;
		Sprite m_ProjectileSprite;
		glm::vec2 m_ProjectileSize;
		float m_ProjectileSpeed;
		glm::vec2* m_Position;
		glm::vec2 m_Direction;
	};
}

