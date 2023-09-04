#pragma once

#include "glm/glm.hpp"

namespace SpaceInvaders
{
	class GameUtils
	{
	public:
		GameUtils();
		~GameUtils();

		bool IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition);
		void AddToScore(int points) { m_Score += points; }

		glm::vec2 GetGameSpace() { return m_GameSpace; }
		glm::vec2 GetMargin() { return m_Margin; }
		int GetEdgePadding() { return m_EdgePadding; }
		int GetScore() { return m_Score; }

		void IncrementWave() { m_Wave++; }
		int GetWave() { return m_Wave; }

	private:
		glm::vec2 m_GameSpace;
		glm::vec2 m_Margin;
		int m_EdgePadding;
		
		int m_Wave;
		int m_Score;
	};
}

