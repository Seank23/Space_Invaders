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
		Alien(int type);
		~Alien();

		virtual void Move(glm::vec2 position) override;
		void Shoot(float distanceToLive) { m_Laser->Shoot(distanceToLive); }
		int TakeDamage();
		void Destroy() { m_IsAlive = false; }

		Laser& GetLaser() { return *m_Laser; }
		float GetShootChance() { return m_ShootChance; }
		bool GetIsAlive() { return m_IsAlive; }
		int GetPoints() { return m_Points; }

		void SetShootChance(float chance) { m_ShootChance = chance; }
		void SetIsAlive(bool alive) { m_IsAlive = alive; }

	private:
		int m_Type;
		int m_Points;
		int m_Lives;
		Laser* m_Laser;
		float m_ShootChance = 0.02f;
		bool m_IsAlive = true;
	};
}

