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
		void TakeDamage();

		virtual void SetSprite(Sprite& sprite) override { m_Sprites.emplace_back(sprite); }
		Sprite& GetSprite(int animationTime);

		Laser& GetLaser() { return *m_Laser; }
		float GetShootChance() { return m_ShootChance; }
		bool GetIsAlive() { return m_IsAlive; }

	private:
		std::vector<Sprite> m_Sprites;
		Laser* m_Laser;
		float m_ShootChance = 0.00015;
		bool m_IsAlive = true;
	};
}

