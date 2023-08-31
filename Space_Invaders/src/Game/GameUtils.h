#pragma once

#include "glm/glm.hpp"

namespace SpaceInvaders
{
	class GameUtils
	{
	public:
		GameUtils(glm::vec2 gameSpace, int edgePadding);
		~GameUtils();

		bool IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition);
		void AddToScore(int points) { m_Score += points; }

		glm::vec2 GetGameSpace() { return m_GameSpace; }
		int GetEdgePadding() { return m_EdgePadding; }
		int GetScore() { return m_Score; }

	private:
		glm::vec2 m_GameSpace;
		int m_EdgePadding;

		int m_Score;
	};
}

