#include "Projectile.h"

namespace SpaceInvaders
{
	Projectile::Projectile(glm::vec2 size)
		: Actor(size), m_DistanceToLive(1000.0f)
	{

	}

	Projectile::~Projectile()
	{

	}

	void Projectile::Move(glm::vec2 position)
	{
		m_DistanceToLive -= glm::abs(position.y);
		Actor::Move(position);
	}
}