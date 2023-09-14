#include "GameStateManager.h"

namespace SpaceInvaders
{
	GameStateManager::GameStateManager()
        : m_Wave(0), m_Score(0)
	{
	}

    bool GameStateManager::IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition)
    {
        return ((actorPosition.x + moveVelocity.x) >= s_EdgePadding && (actorPosition.x + moveVelocity.x) <= s_GameSpace.x - s_EdgePadding) &&
            ((actorPosition.y + moveVelocity.y) >= s_EdgePadding && (actorPosition.y + moveVelocity.y) <= s_GameSpace.y - s_EdgePadding);
    }

    void GameStateManager::CullProjectiles()
    {
        m_Projectiles.erase(
            std::remove_if(
                m_Projectiles.begin(),
                m_Projectiles.end(),
                [](std::shared_ptr<Projectile> p) { return p->GetDistanceToLive() <= 0; }
            ),
            m_Projectiles.end()
        );
    }
}
