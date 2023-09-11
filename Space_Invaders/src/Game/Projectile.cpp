#include "Projectile.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
	Projectile::Projectile(float speed, glm::vec2 direction)
		: Actor(), m_Direction(direction), m_Speed(speed), m_DistanceToLive(1000.0f), m_Missed(false)
	{
		m_Animator->CreateAnimation("Missed", [](int activeSprite) { return 0; }, 250);
		m_Animator->SetActiveSpriteIndex(1);
	}

	Projectile::~Projectile()
	{

	}

	void Projectile::Move(glm::vec2 position)
	{
		if (!m_Missed)
		{
			m_DistanceToLive -= glm::abs(position.y);
			m_Position = { m_Position.x + position.x, m_Position.y + position.y };
		}
		CalculateTransform();
	}

	bool Projectile::HasCollided(Actor& actor)
	{
		glm::vec2 position = actor.GetPosition();
		glm::vec2 size = actor.GetSprite().GetSize();
		glm::vec2 bottomLeft = { position.x - size.x / 2, position.y - size.y / 2 };
		glm::vec2 topRight = { position.x + size.x / 2, position.y + size.y / 2 };

		return glm::all(glm::greaterThan(m_Position, bottomLeft) && glm::lessThan(m_Position, topRight));
	}

	void Projectile::CheckForMiss(float ts)
	{
		if (!m_Missed && m_DistanceToLive <= 0.0f)
		{
			m_Animator->Animate("Missed");
			m_Missed = true;
			m_DistanceToLive = 10.0f;
		}
		if (m_Missed)
		{
			std::vector<std::string> expiredAnimations = m_Animator->UpdateAnimationTimers(ts);
			for (std::string anim : expiredAnimations)
			{
				if (anim == "Missed")
					m_DistanceToLive = 0.0f;
			}
		}
	}

	void Projectile::CalculateTransform()
	{
		glm::vec2 size = GetSprite().GetSize();
		m_Transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, -1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	}
}