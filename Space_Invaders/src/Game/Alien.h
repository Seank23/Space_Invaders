#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Laser.h"
#include "Engine/SpriteAnimator.h"

#include <memory>
#include <vector>

namespace SpaceInvaders
{
	class Alien : public Actor
	{
	public:
		Alien(int type);
		~Alien();

		virtual void Move(glm::vec2 position) override;
		void Shoot(float distanceToLive) { m_Laser->Shoot(distanceToLive); }
		void TakeDamage();
		void Destroy() { m_IsAlive = false; }

		Laser& GetLaser() { return *m_Laser; }
		float GetShootChance() { return m_ShootChance; }
		bool GetIsAlive() { return m_IsAlive; }

	private:
		int m_Type;
		Laser* m_Laser;
		float m_ShootChance = 0.00025;
		bool m_IsAlive = true;
	};
}

