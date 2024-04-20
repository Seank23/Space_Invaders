#include "Game.h"
#include "SpriteData.h"
#include "Engine/BinaryTexture.h"
#include "Engine/SpriteAnimator.h"
#include "Log.h"
#include "Engine/Audio/AudioUtils.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace SpaceInvaders
{
    Game::Game()
        : m_Shader(nullptr), m_Renderer(nullptr), m_Player(nullptr), m_AlienSwarm(nullptr), m_AlienShip(nullptr), m_Ground(nullptr),
        m_GroundTransform(glm::mat4(1.0f)), m_StateManager(GameStateManager::Instance())
    {
        m_GameTimer.start();
    }

    Game::~Game()
    {
        delete m_Shader;
        delete m_Renderer; 
        delete m_Player;
    }

    void Game::Init(int* windowLayout)
    {
        glm::mat4 proj = glm::ortho(0.0f, GameStateManager::s_GameSpace.x, GameStateManager::s_GameSpace.y, 0.0f, -1.0f, 1.0f);
        m_Shader = new Shader("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Projection", proj);
        m_Shader->SetUniform2f("u_WindowLayout", windowLayout[0], windowLayout[1]);
        m_Renderer = new SpriteRenderer(*m_Shader);

        std::srand(std::time(0));

        m_Ground = new Sprite(BinaryTexture::Create(SpriteData::GroundSprite, SpriteData::LayoutGroundSprite), { 0.0f, 0.0f });
        m_GroundTransform = glm::translate(glm::mat4(1.0f), { GameStateManager::s_GameSpace.x / 2, GameStateManager::s_GameSpace.y - GameStateManager::s_Margin.y, -1.0f }) *
            glm::scale(glm::mat4(1.0f), { GameStateManager::s_GameSpace.x, 2.0f, 1.0f });

        m_Player = new Player();
        m_Player->SetPosition({ 50.0f, 680.0f });

        m_AlienSwarm = std::make_unique<AlienSwarm>();
        m_AlienSwarm->Init({ GameStateManager::s_GameSpace.x / 7, GameStateManager::s_GameSpace.y / 4 });
        m_InitAliens = true;

        m_AlienShip = std::make_unique<AlienSwarm>(true);

        for (int i = 0; i < 4; i++)
            m_StateManager->AddShield(std::make_shared<Shield>(glm::vec2(120.0f + (i * 120.0f), 620.0f )));

        m_ScoreLabelText = std::make_unique<TextSprite>("score<1> hi-score", glm::vec2(210.0f, 20.0f), glm::vec2(360.0f, 22.0f));
        m_Player1ScoreText = std::make_unique<TextSprite>("0000", glm::vec2(110.0f, 65.0f), glm::vec2(80.0f, 22.0f));
        m_HighScoreText = std::make_unique<TextSprite>("0000", glm::vec2(280.0f, 65.0f), glm::vec2(80.0f, 22.0f));
        m_LivesText = std::make_unique<TextSprite>("3", glm::vec2(40.0f, 765.0f), glm::vec2(20.0f, 22.0f));
        m_LivesLeftIcons = std::make_unique<TextSprite>("``_____", glm::vec2(230.0f, 765.0f), glm::vec2(300.0f, 24.0f), SpriteData::LayoutPlayerSprite);
        m_CreditsText = std::make_unique<TextSprite>("credit 00", glm::vec2(480.0f, 765.0f), glm::vec2(180.0f, 22.0f));
        m_GameOverText = std::make_unique<TextSprite>("game over", glm::vec2(300.0f, 180.0f), glm::vec2(180.0f, 22.0f));
    }

    void Game::Update(float ts)
    {
        m_Renderer->DrawSprite(*m_Ground, m_GroundTransform); // Always draw ground
        m_StateManager->SetPlayerPosition(m_Player->GetPosition().x);

        if (m_GameOver)
            if (HandleGameOver(ts)) return;

        if (m_AlienSwarm->CheckWaveComplete())
            StartNextWave();

        if (m_AlienSwarm->HasReachedGround())
            m_GameOver = true;
        
        if (m_PlayerHit)
            HandlePlayerHit(ts);

        HandleProjectiles(ts);
        HandleAnimations(ts);
        HandleMove(ts);

        DrawSprites(ts);

        m_FrameCount++;
    }

    bool Game::HandleGameOver(float ts)
    {
        m_GameOverTimer -= ts;
        if (m_GameOverTimer <= 0.0f)
        {
            // Start new game
            m_GameOverTimer = 3.0f;
            m_GameOver = false;
            m_StateManager->ResetGame();
            m_Player->ResetLives();
            m_AlienSwarm->Init({ GameStateManager::s_GameSpace.x / 7, (GameStateManager::s_GameSpace.y / 4) });
            m_InitAliens = true;
            for (auto& shield : m_StateManager->GetShields())
                shield->Reset();
            int highScore = m_StateManager->GetHighScore();
            m_HighScoreText->SetText(std::string(4 - std::fmin(4, (int)std::to_string(highScore).length()), '0') + std::to_string(highScore));
            m_Player1ScoreText->SetText("0000");
            m_LivesText->SetText("3");
            m_LivesLeftIcons->SetText("``_____");
            m_Player->SetPosition({ 50.0f, 680.0f });
        }
        else
        {
            DrawSprites(ts);
            return false;
        }
        return true;
    }

    void Game::StartNextWave()
    {
        m_StateManager->IncrementWave();
        m_AlienSwarm->Init({ GameStateManager::s_GameSpace.x / 7, (GameStateManager::s_GameSpace.y / 4) + (50 * m_StateManager->GetWave()) });
        m_Player->AddLife();
        int livesLeft = m_Player->GetLives();
        m_LivesText->SetText(std::to_string(livesLeft));
        m_LivesLeftIcons->SetText(std::string(livesLeft - 1, '`') + std::string(7 - (livesLeft - 1), '_'));
        m_InitAliens = true;
    }

    void Game::HandleProjectiles(float ts)
    {
        auto& projectiles = m_StateManager->GetProjectiles();
        auto& shields = m_StateManager->GetShields();
        for (auto& projectile : projectiles)
        {
            if (m_PlayerHit)
                projectile->SetDistanceToLive(0);
            projectile->Move(ts * projectile->GetSpeed() * projectile->GetDirection());
            projectile->CheckForMiss(ts);

            if (glm::dot(projectile->GetDirection(), glm::vec2(0.0f, 1.0f)) < 0.0f)
            {
                // Check alien collision
                bool alienHit = m_AlienSwarm->CheckProjectileCollision(*projectile);
                bool shipHit = false;
                if (!alienHit)
                    shipHit = m_AlienShip->CheckProjectileCollision(*projectile);

                if (alienHit || shipHit)
                {
                    alienHit ? m_AlienSwarm->StopSwarm() : m_AlienShip->StopSwarm();
                    int score = m_StateManager->GetScore();
                    std::string scoreText = std::string(4 - std::fmin(4, (int)std::to_string(score).length()), '0') + std::to_string(score);
                    m_Player1ScoreText->SetText(scoreText);
                }
                if (projectile->GetDistanceToLive() == 0) continue;
                
                // Check projectile - projectile collision
                for (int i = 0; i < projectiles.size(); i++)
                {
                    if (glm::dot(projectile->GetDirection(), projectiles[i]->GetDirection()) > 0.0f || projectiles[i]->GetDistanceToLive() == 0) continue;
                    if (projectile->HasCollided(*projectiles[i]))
                    {
                        projectile->SetDistanceToLive(0);
                        projectiles[i]->SetDistanceToLive(0);
                        projectile->CheckForMiss(ts);
                    }
                }
            }
            else
            {
                // Check player collision
                if (projectile->HasCollided(*m_Player))
                {
                    projectile->SetDistanceToLive(0);
                    m_Player->TakeDamage();
                    m_PlayerHit = true;
                }
            }
            // Check shield collision
            if (projectile->GetDistanceToLive() >= 10)
            {
                float shieldCollisionThresholdTop = (shields[0]->GetPosition().y - shields[0]->GetSize().y / 2) - 10.0f;
                float shieldCollisionThresholdBottom = (shields[0]->GetPosition().y + shields[0]->GetSize().y / 2) + 10.0f;
                if (projectile->GetPosition().y > shieldCollisionThresholdTop && projectile->GetPosition().y < shieldCollisionThresholdBottom)
                {
                    for (auto& shield : shields)
                    {
                        glm::vec2 hitPosition = shield->GetHitPosition(projectile->GetPosition().x, (int)projectile->GetDirection().y);
                        if (hitPosition.x > -1 && hitPosition.y > -1 && projectile->GetPosition().y >= shieldCollisionThresholdTop + hitPosition.y * 2.5f)
                        {
                            shield->TakeDamage(hitPosition, (int)projectile->GetDirection().y);
                            projectile->SetDistanceToLive(0);
                            projectile->CheckForMiss(ts);
                        }
                    }
                }
            }
        }
        m_StateManager->CullProjectiles();
    }

    void Game::HandlePlayerHit(float ts)
    {
        m_AlienSwarm->StopSwarm();
        if (m_FrameCount % 10 == 0)
            m_Player->Animate("Hit");

        m_PlayerHitTimer -= ts;
        if (m_PlayerHitTimer <= 0.0f)
        {
            int livesLeft = m_Player->GetLives();
            if (livesLeft == 0)
            {
                m_GameOver = true;
                INFO("Game Over!");
            }
            if (!m_GameOver) m_AlienSwarm->RestartSwarm();
            m_LivesText->SetText(std::to_string(livesLeft));
            m_LivesLeftIcons->SetText(std::string(std::fmax(livesLeft - 1, 0), '`') + std::string(7 - std::fmax(livesLeft - 1, 0), '_'));
            m_PlayerHit = false;
            m_PlayerHitTimer = 1.0f;
            m_Player->SetPosition({ 50.0f, 680.0f });
            m_Player->GetAnimator()->SetActiveSpriteIndex(0);
        }
    }

    void Game::HandleAnimations(float ts)
    {
        m_AlienSwarm->CheckAnimationsAndCull(ts, [this]() { m_AlienSwarm->RestartSwarm(); });
        m_AlienShip->CheckAnimationsAndCull(ts, [this]()
            {
                for (auto& ship : m_AlienShip->GetAliens())
                    ship->Animate("Killed");
            });
        m_AlienSwarm->CalculateShootChance();
    }

    void Game::HandleMove(float ts)
    {
        // Handle alien move
        if (!m_InitAliens && (int)m_GameTimer.elapsedMilliseconds() % (int)((1.0f / m_SwarmFps) * 1000) < (int)(1000 * ts))
        {
            if (!m_AlienSwarm->IsStopped()) m_AlienSwarm->MoveAliens();
            if (!m_AlienShip->IsStopped()) m_AlienShip->MoveAliens();
        }

        // Handle player move
        if (m_StateManager->IsMoveValid({ ts * m_MoveVelocity, 0.0f }, m_Player->GetPosition()))
            m_Player->Move({ ts * m_MoveVelocity, 0.0f });

        if (m_AlienShip->CheckWaveComplete() && !m_GameOver && std::rand() % (int)(1.0f / m_ShipChance) == 0)
        {
            m_AlienShip->Init({ 650.0f, 120.0f });
            m_AlienShip->RestartSwarm();
        }
    }

    void Game::DrawSprites(float ts)
    {
        auto& aliens = m_AlienSwarm->GetAliens();
        auto& projectiles = m_StateManager->GetProjectiles();
        auto& shields = m_StateManager->GetShields();
        if (m_InitAliens)
        {
            if (m_AlienSwarm->IsStopped()) m_AlienSwarm->RestartSwarm();
            int alienIndex = m_AlienSwarm->GetAlienIndex();
            for (int i = 0; i < alienIndex; i++)
                m_Renderer->DrawSprite(aliens[i]->GetSprite(), aliens[i]->GetTransform());
            if (alienIndex == aliens.size() - 1)
            {
                m_InitAliens = false;
                m_AlienSwarm->SetAlienIndex(0);
            }

            if ((int)m_GameTimer.elapsedMilliseconds() % (int)((1.0f / m_SwarmFps) * 1000) < (int)(1000 * ts))
                m_AlienSwarm->SetAlienIndex(alienIndex + 1);
        }
        else
        {
            if (!m_GameOver)
            {
                for (auto& projectile : projectiles)
                    m_Renderer->DrawSprite(projectile->GetSprite(), projectile->GetTransform());
                m_Renderer->DrawSprite(m_Player->GetSprite(), m_Player->GetTransform());
            }
            for (auto& shield : shields)
                m_Renderer->DrawSprite(shield->GetSprite(), shield->GetTransform());
            for (auto& alien : aliens)
                m_Renderer->DrawSprite(alien->GetSprite(), alien->GetTransform());
            for (auto& alien : m_AlienShip->GetAliens())
                m_Renderer->DrawSprite(alien->GetSprite(), alien->GetTransform());

            // Draw text
            m_Renderer->DrawSprite(m_ScoreLabelText->GetSprite(), m_ScoreLabelText->GetTransform());
            m_Renderer->DrawSprite(m_Player1ScoreText->GetSprite(), m_Player1ScoreText->GetTransform());
            m_Renderer->DrawSprite(m_HighScoreText->GetSprite(), m_HighScoreText->GetTransform());
            m_Renderer->DrawSprite(m_LivesText->GetSprite(), m_LivesText->GetTransform());
            m_Renderer->DrawSprite(m_LivesLeftIcons->GetSprite(), m_LivesLeftIcons->GetTransform());
            m_Renderer->DrawSprite(m_CreditsText->GetSprite(), m_CreditsText->GetTransform());
            if (m_GameOver)
                m_Renderer->DrawSprite(m_GameOverText->GetSprite(), m_GameOverText->GetTransform());
        }
    }

    void Game::InputListener(int key, int action)
    {
        if (!m_PlayerHit && !m_InitAliens)
        {
            switch (key)
            {
            case GLFW_KEY_LEFT:
                if (action == GLFW_PRESS) m_MoveVelocity = -300.0f;
                else if (action == GLFW_RELEASE) m_MoveVelocity = 0.0f;
                break;
            case GLFW_KEY_RIGHT:
                if (action == GLFW_PRESS) m_MoveVelocity = 300.0f;
                else if (action == GLFW_RELEASE) m_MoveVelocity = 0.0f;
                break;
            case GLFW_KEY_UP:
                if (action == GLFW_PRESS)
                {
                    if (m_GameTimer.elapsedMilliseconds() - m_LastShootMs >= m_PlayerShootCooldownMs)
                    {
                        m_Player->Shoot(m_Player->GetPosition().y - GameStateManager::s_Margin.x);
                        m_LastShootMs = (int)m_GameTimer.elapsedMilliseconds();
                    }
                }
            }
        }
        else
        {
            m_MoveVelocity = 0.0f;
        }
    }
}
