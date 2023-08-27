#pragma once
#include "Actor.h"
#include "Laser.h"

#include <memory>

namespace SpaceInvaders
{
	class Player : public Actor
	{
	public:
		Player(glm::vec2 size);
		~Player();

		void Shoot(float distanceToLive) { m_Laser->Shoot(distanceToLive); }

		std::shared_ptr<Laser> GetLaser() { return m_Laser; }

	private:
		std::shared_ptr<Laser> m_Laser;
	};
}

