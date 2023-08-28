#include "Projectile.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
	Projectile::Projectile(glm::vec2 size)
		: Actor(size), m_Speed(200.0f), m_DistanceToLive(1000.0f)
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

	bool Projectile::HasCollided(Actor& actor)
	{
		glm::vec2 position = actor.GetPosition();
		glm::vec2 size = actor.GetSize();
		glm::vec2 bottomLeft = { position.x - size.x / 2, position.y - size.y / 2 };
		glm::vec2 topRight = { position.x + size.x / 2, position.y + size.y / 2 };

		return glm::all(glm::greaterThan(m_Position, bottomLeft) && glm::lessThan(m_Position, topRight));
	}

	void Projectile::CalculateTransform()
	{
		m_Transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, -1.0f })
			* glm::scale(glm::mat4(1.0f), { m_Size.x, m_Size.y, 1.0f });
	}
}