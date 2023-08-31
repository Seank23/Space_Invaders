#pragma once
#include "Sprite.h"

#include <string>
#include <map>
#include <functional>
#include <glm/glm.hpp>

namespace SpaceInvaders
{
	class SpriteAnimator
	{
	public:
		SpriteAnimator();
		~SpriteAnimator();

		void CreateAnimation(std::string name, int (*condition)(int), int durationMs = 0);
		void Animate(std::string name);
		std::vector<std::string> UpdateAnimationTimers(float ts);
		//void SetOnSizeChange(std::function<glm::vec2> onSizeChange) { m_OnSizeChange = onSizeChange; }

		void AddSprite(int id, Sprite& sprite, glm::vec2 size);
		Sprite& GetActiveSprite() { return m_Sprites[m_ActiveSprite]; }
		glm::vec2 GetActiveSpriteSize() { return m_Sizes[m_ActiveSprite]; }

	private:
		int m_ActiveSprite = 0;
		std::map<int, Sprite> m_Sprites;
		std::map<int, glm::vec2> m_Sizes;
		std::map<std::string, int (*)(int)> m_Animations;
		std::vector<std::string> m_AnimationNames;
		std::map<std::string, int> m_AnimationDuration;
		std::map<std::string, float> m_AnimationTimers;
		//std::function<glm::vec2> m_OnSizeChange;
	};
}

