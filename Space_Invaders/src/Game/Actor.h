#pragma once
#include "Engine/Sprite.h"
#include "Engine/SpriteAnimator.h"

#include "glm/glm.hpp"

namespace SpaceInvaders
{
	class Actor
	{
	public:
		Actor();
		Actor(glm::vec2 size);
		~Actor();

		virtual void Move(glm::vec2 position);
		void Animate(std::string name) { m_Animator.Animate(name); }

		void SetPosition(glm::vec2 position);
		void SetSize(glm::vec2 size);
		void AddSprite(int id, Sprite& sprite, glm::vec2 size) { m_Animator.AddSprite(id, sprite, size); }

		Sprite& GetSprite() { return m_Animator.GetActiveSprite(); }
		SpriteAnimator& GetAnimator() { return m_Animator; }
		glm::mat4& GetTransform() { return m_Transform; }
		glm::vec2& GetPosition() { return m_Position; }
		glm::vec2& GetSize() { return m_Size; }
		glm::vec2& GetSpriteSize() { return m_Animator.GetActiveSpriteSize(); }

	protected:
		virtual void CalculateTransform();

		glm::vec2 m_Position;
		glm::vec2 m_Size;
		glm::mat4 m_Transform;
		Sprite m_Sprite;
		SpriteAnimator m_Animator;
	};
}
