#pragma once
#include "Actor.h"
#include "Engine/SpriteRenderer.h"
#include "Engine/Shader.h"
#include "Projectile.h"

#include <memory>

namespace SpaceInvaders
{
	class Player : public Actor
	{
	public:
		Player(glm::vec2 size);
		~Player();

		void Shoot(float distanceToLive);
		void CullProjectiles();

		std::vector<std::shared_ptr<Projectile>> GetProjectiles() { return m_Projectiles; }
		glm::vec2 GetShootDirection() { return m_ShootDirection; }

	private:
		std::vector<std::shared_ptr<Projectile>> m_Projectiles;
		std::shared_ptr<Sprite> m_ProjectileSprite;
		glm::vec2 m_ShootDirection;
	};
}

