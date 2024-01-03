#pragma once
#include "Actor.h"
#include "Engine/Sprite.h"

#include "glm/glm.hpp"

#include <iterator>
#include <vector>

namespace SpaceInvaders
{
	class Shield : public Actor
	{
	public:
		Shield(glm::vec2 position);
		~Shield();

		virtual Sprite& GetSprite() override { return m_Sprite; }
		glm::mat4 GetTransform() { return m_Transform; }
		glm::vec2 GetSize() { return m_Size; }

		glm::vec2 GetHitPosition(int posX);
		void TakeDamage(glm::vec2 position);
		void Reset();

	private:
		std::vector<uint8_t> m_Pixels;
		glm::vec2 m_Size;
		glm::vec2 m_SpriteLayout;
		std::vector<int> m_DamageDepth;

		void SubtractPixels(std::vector<uint8_t> pixels, glm::vec2 size, glm::vec2 position);
		void CalculateDamageDepth();
	};
}

