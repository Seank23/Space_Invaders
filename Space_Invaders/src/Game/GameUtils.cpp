#include "GameUtils.h"

namespace SpaceInvaders
{
	GameUtils::GameUtils()
		: m_GameSpace({ 600.0f, 800.0f }), m_Margin({ 100.0f, 50.0f }), m_EdgePadding(35), m_Score(0)
	{
	}

	GameUtils::~GameUtils()
	{

	}

	bool GameUtils::IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition)
	{
		return ((actorPosition.x + moveVelocity.x) >= m_EdgePadding && (actorPosition.x + moveVelocity.x) <= m_GameSpace.x - m_EdgePadding) &&
			((actorPosition.y + moveVelocity.y) >= m_EdgePadding && (actorPosition.y + moveVelocity.y) <= m_GameSpace.y - m_EdgePadding);
	}
}
