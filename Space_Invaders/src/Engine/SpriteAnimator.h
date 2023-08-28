#pragma once
#include "Sprite.h"

#include <string>
#include <map>

namespace SpaceInvaders
{
	class SpriteAnimator
	{
	public:
		SpriteAnimator();
		~SpriteAnimator();

		void CreateAnimation(std::string name, int (*condition)(int));
		void Animate(std::string name);

		void AddSprite(int id, Sprite& sprite);
		Sprite& GetActiveSprite() { return m_Sprites[m_ActiveSprite]; }

	private:
		int m_ActiveSprite = 0;
		std::map<int, Sprite> m_Sprites;
		std::map<std::string, int (*)(int)> m_Animations;
	};
}

