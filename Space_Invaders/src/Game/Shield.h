#pragma once
#include "Actor.h"
#include "Engine/Sprite.h"

#include "glm/glm.hpp"

namespace SpaceInvaders
{
	class Shield : public Actor
	{
	public:
		Shield(glm::vec2 position);
		~Shield();

		virtual Sprite& GetSprite() override { return m_Sprite; }
		glm::mat4 GetTransform() { return m_Transform; }
	};
}

