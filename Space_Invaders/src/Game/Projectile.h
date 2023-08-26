#pragma once
#include "Actor.h"

namespace SpaceInvaders
{
	class Projectile : public Actor
	{
	public:
		Projectile(glm::vec2 size);
		~Projectile();

		virtual void Move(glm::vec2 position) override;

		void SetDistanceToLive(float dtl) { m_DistanceToLive = dtl; }

		float GetSpeed() { return m_Speed; }
		float GetDistanceToLive() { return m_DistanceToLive; }

	private:
		float m_Speed = 2.0f;
		float m_DistanceToLive;
	};
}

