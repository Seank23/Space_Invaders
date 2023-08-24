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

		void Move(glm::vec2 position);

		void SetPosition(glm::vec2 position);
		void SetSize(glm::vec2 size);
		virtual void SetSprite(Sprite& sprite) { m_Sprite = std::make_shared<Sprite>(sprite); }

		Sprite& GetSprite() { return *m_Sprite; }
		glm::mat4& GetTransform() { return m_Transform; }
		glm::vec2& GetPosition() { return m_Position; }

	private:
		void CalculateTransform();

		glm::vec2 m_Position;
		glm::vec2 m_Size;
		glm::mat4 m_Transform;
		std::shared_ptr<Sprite> m_Sprite;
	};
}
