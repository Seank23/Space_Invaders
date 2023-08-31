#include "GameUtils.h"

namespace SpaceInvaders
{
	GameUtils::GameUtils(glm::vec2 gameSpace, int edgePadding)
		: m_GameSpace(gameSpace), m_EdgePadding(edgePadding), m_Score(0)
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
