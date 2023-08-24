#pragma once
#include "Actor.h"
#include "Engine/SpriteRenderer.h"

#include <memory>
#include <vector>

namespace SpaceInvaders
{
	class Alien : public Actor
	{
	public:
		Alien(glm::vec2 size);
		~Alien();

		virtual void SetSprite(Sprite& sprite) override { m_Sprites.push_back(sprite); }
		Sprite& GetSprite(int animationTime);

	private:
		std::vector<Sprite> m_Sprites;
	};
}

