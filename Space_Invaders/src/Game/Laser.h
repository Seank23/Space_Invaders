#pragma once
#include "Projectile.h"
#include "GameStateManager.h"
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

		glm::vec2 GetDirection() { return m_Direction; }
		void SetProjectileSpeed(float speed) { m_ProjectileSpeed = speed; }

	private:
		std::shared_ptr<GameStateManager> m_StateManager;
		std::map<int, Sprite> m_ProjectileSprites;
		float m_ProjectileSpeed;
		glm::vec2* m_Position;
		glm::vec2 m_Direction;
	};
}

