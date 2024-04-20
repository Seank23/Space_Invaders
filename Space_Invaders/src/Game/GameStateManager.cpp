#include "GameStateManager.h"
#include "Player.h"

#include "Engine/Audio/AudioUtils.h"

namespace SpaceInvaders
{
	GameStateManager::GameStateManager()
        : m_Wave(0), m_Score(0), m_HighScore(0), m_PlayerPosition(0)
	{
        auto devices = AudioEngine::AudioUtils::EnumerateDevices();
        m_AudioHandler = new AudioHandler(devices[0]);
	}

    bool GameStateManager::IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition)
    {
        return ((actorPosition.x + moveVelocity.x) >= s_EdgePadding && (actorPosition.x + moveVelocity.x) <= s_GameSpace.x - s_EdgePadding) &&
            ((actorPosition.y + moveVelocity.y) >= s_EdgePadding && (actorPosition.y + moveVelocity.y) <= s_GameSpace.y - s_EdgePadding);
    }

    void GameStateManager::ResetGame()
    {
        m_HighScore = std::fmax(m_Score, m_HighScore);
        m_Score = 0;
        m_Wave = 0;
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
