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
		~Actor();

		virtual void Move(glm::vec2 position);
		void Animate(std::string name);

		void SetPosition(glm::vec2 position);
		void AddSprite(int id, Sprite& sprite) { m_Animator->AddSprite(id, sprite); }

		Sprite& GetSprite() { return m_Animator->GetActiveSprite(); }
		std::shared_ptr<SpriteAnimator> GetAnimator() { return m_Animator; }
		glm::mat4& GetTransform() { return m_Transform; }
		glm::vec2& GetPosition() { return m_Position; }

	protected:
		virtual void CalculateTransform();

		glm::vec2 m_Position;
		glm::mat4 m_Transform;
		Sprite m_Sprite;
		std::shared_ptr<SpriteAnimator> m_Animator;
	};
}
