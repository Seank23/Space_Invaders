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
		Laser(int type, glm::vec2* position, glm::vec2 direction);
		~Laser();

		void Shoot(float distanceToLive);
		void CullProjectiles();

		std::vector<Projectile>* GetProjectiles() { return &m_Projectiles; }
		glm::vec2 GetDirection() { return m_Direction; }
		void SetProjectileSpeed(float speed) { m_ProjectileSpeed = speed; }

	private:
		std::vector<Projectile> m_Projectiles;
		std::map<int, Sprite> m_ProjectileSprites;
		float m_ProjectileSpeed;
		glm::vec2* m_Position;
		glm::vec2 m_Direction;
	};
}

