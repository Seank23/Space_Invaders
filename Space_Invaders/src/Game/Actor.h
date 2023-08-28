#pragma once
#include "Engine/Sprite.h"

#include "glm/glm.hpp"

namespace SpaceInvaders
{
	class Actor
	{
	public:
		Actor(glm::vec2 size);
		~Actor();

		virtual void Move(glm::vec2 position);

		void SetPosition(glm::vec2 position);
		void SetSize(glm::vec2 size);
		virtual void SetSprite(Sprite& sprite) { m_Sprite = sprite; }

		Sprite& GetSprite() { return m_Sprite; }
		glm::mat4& GetTransform() { return m_Transform; }
		glm::vec2& GetPosition() { return m_Position; }
		glm::vec2& GetSize() { return m_Size; }

	protected:
		virtual void CalculateTransform();

		glm::vec2 m_Position;
		glm::vec2 m_Size;
		glm::mat4 m_Transform;
		Sprite m_Sprite;
	};
}
