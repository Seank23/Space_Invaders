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
		Laser(glm::vec2* position, glm::vec2 direction, std::shared_ptr<Sprite> projectileSprite, glm::vec2 projectileSize);
		~Laser();

		void Shoot(float distanceToLive);
		void CullProjectiles();

		std::vector<std::shared_ptr<Projectile>> GetProjectiles() { return m_Projectiles; }
		glm::vec2 GetDirection() { return m_Direction; }

	private:
		std::vector<std::shared_ptr<Projectile>> m_Projectiles;
		std::shared_ptr<Sprite> m_ProjectileSprite;
		glm::vec2 m_ProjectileSize;
		glm::vec2* m_Position;
		glm::vec2 m_Direction;
	};
}

