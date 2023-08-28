#include "Actor.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
	Actor::Actor(glm::vec2 size)
		: m_Position({ 0.0f, 0.0f }), m_Size(size), m_Transform(glm::mat4(1.0f))
	{
	}

	Actor::~Actor()
	{

	}

	void Actor::Move(glm::vec2 position)
	{
		m_Position = { m_Position.x + position.x, m_Position.y + position.y };
		CalculateTransform();
	}

	void Actor::SetPosition(glm::vec2 position)
	{
		m_Position = position;
		CalculateTransform();
	}

	void Actor::SetSize(glm::vec2 size)
	{
		m_Size = size;
		CalculateTransform();
	}

	void Actor::CalculateTransform()
	{
		m_Transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { m_Size.x, m_Size.y, 1.0f });
	}
}