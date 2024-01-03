#pragma once
#include "Actor.h"
#include "Laser.h"

#include <memory>

namespace SpaceInvaders
{
	class Player : public Actor
	{
	public:
		Player();
		~Player();

		void Shoot(float distanceToLive) { m_Laser->Shoot(distanceToLive); }
		int TakeDamage();
		void AddLife() { m_Lives++; }
		void ResetLives() { m_Lives = 3; }

		Laser& GetLaser() { return *m_Laser; }
		int GetLives() { return m_Lives; }

	private:
		Laser* m_Laser;
		int m_Lives = 3;
	};
}

