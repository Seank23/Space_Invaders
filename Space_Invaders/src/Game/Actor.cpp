#include "Actor.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
	Actor::Actor()
		: m_Position({ 0.0f, 0.0f }), m_Transform(glm::mat4(1.0f)), m_Animator(nullptr)
	{
		m_Animator = std::make_shared<SpriteAnimator>();
	}

	Actor::~Actor()
	{
		
	}

	void Actor::Move(glm::vec2 position)
	{
		m_Position = { m_Position.x + position.x, m_Position.y + position.y };
		CalculateTransform();
	}

	void Actor::Animate(std::string name)
	{
		m_Animator->Animate(name);
		CalculateTransform();
	}

	void Actor::SetPosition(glm::vec2 position)
	{
		m_Position = position;
		CalculateTransform();
	}

	void Actor::CalculateTransform()
	{
		glm::vec2 size = GetSprite().GetSize();
		m_Transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	}
}