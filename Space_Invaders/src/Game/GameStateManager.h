#pragma once
#include "Projectile.h"
#include "Shield.h"

#include "AudioHandler.h"

#include <vector>

namespace SpaceInvaders
{
	class GameStateManager
	{
    public:
        GameStateManager(GameStateManager const&) = delete;
        GameStateManager& operator=(GameStateManager const&) = delete;

        static std::shared_ptr<GameStateManager> Instance()
        {
            static std::shared_ptr<GameStateManager> s{ new GameStateManager };
            return s;
        }

    private:
        GameStateManager();


    public:
        static constexpr glm::vec2 s_GameSpace = { 600.0f, 800.0f };
        static constexpr glm::vec2 s_Margin = { 100.0f, 50.0f };
        static const int s_EdgePadding = 35;

        AudioHandler& GetAudioHandler() { return *m_AudioHandler; }

        bool IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition);

        void AddToScore(int points) { m_Score += points; }
        int GetScore() { return m_Score; }
        int GetHighScore() { return m_HighScore; }
        void ResetGame();

        void IncrementWave() { m_Wave < 3 && m_Wave++; }
        int GetWave() { return m_Wave; }

        void AddProjectile(std::shared_ptr<Projectile> p) { m_Projectiles.push_back(p); }
        void AddShield(std::shared_ptr<Shield> s) { m_Shields.push_back(s); }
        std::vector<std::shared_ptr<Projectile>>& GetProjectiles() { return m_Projectiles; }
        std::vector<std::shared_ptr<Shield>>& GetShields() { return m_Shields; }
        void CullProjectiles();

        void SetPlayerPosition(int position) { m_PlayerPosition = position; }
        int GetPlayerPosition() { return m_PlayerPosition; }

    private:
        AudioHandler* m_AudioHandler;

        std::vector<std::shared_ptr<Projectile>> m_Projectiles;
        std::vector<std::shared_ptr<Shield>> m_Shields;

        int m_Wave;
        int m_Score;
        int m_HighScore;
        int m_PlayerPosition;
	};
}

