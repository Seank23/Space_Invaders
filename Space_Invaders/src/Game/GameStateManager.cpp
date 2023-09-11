#include "GameStateManager.h"

namespace SpaceInvaders
{
	GameStateManager::GameStateManager()
	{
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
