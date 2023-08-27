#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Laser.h"

#include <memory>
#include <vector>

namespace SpaceInvaders
{
	class Alien : public Actor
	{
	public:
		Alien(glm::vec2 size);
		~Alien();

		void Shoot(float distanceToLive) { m_Laser->Shoot(distanceToLive); }

		virtual void SetSprite(Sprite& sprite) override { m_Sprites.push_back(sprite); }
		Sprite& GetSprite(int animationTime);

		std::shared_ptr<Laser> GetLaser() { return m_Laser; }
		float GetShootChance() { return m_ShootChance; }

	private:
		std::vector<Sprite> m_Sprites;
		std::shared_ptr<Laser> m_Laser;
		float m_ShootChance = 0.00015;
	};
}

