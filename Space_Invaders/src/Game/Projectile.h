#pragma once
#include "Actor.h"

namespace SpaceInvaders
{
	class Projectile : public Actor
	{
	public:
		Projectile(glm::vec2 size, float speed);
		~Projectile();

		virtual void Move(glm::vec2 position) override;
		bool HasCollided(Actor& actor);

		void SetDistanceToLive(float dtl) { m_DistanceToLive = dtl; }
		void SetSpeed(float speed) { m_Speed = speed; }

		float GetSpeed() { return m_Speed; }
		float GetDistanceToLive() { return m_DistanceToLive; }

	private:
		virtual void CalculateTransform() override;

		float m_Speed;
		float m_DistanceToLive;
	};
}
