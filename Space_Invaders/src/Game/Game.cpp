#include "Game.h"
#include "SpriteData.h"
#include "Engine/BinaryTexture.h"
#include "Engine/SpriteAnimator.h"
#include "Log.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace SpaceInvaders
{
    Game::Game()
        : m_Shader(nullptr), m_Renderer(nullptr), m_Player(nullptr), m_AlienSwarm(nullptr), m_Ground(nullptr), m_GroundTransform(glm::mat4(1.0f)),
        m_StateManager(GameStateManager::Instance())
    {
        m_GameTimer.start();
    }

    Game::~Game()
    {
        delete m_Shader;
        delete m_Renderer; 
        delete m_Player;
        delete m_AlienSwarm;
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
        m_Player->SetPosition({ 300.0f, 680.0f });

        m_AlienSwarm = new AlienSwarm();
        m_AlienSwarm->Init({ GameStateManager::s_GameSpace.x / 7, GameStateManager::s_GameSpace.y / 4 });
        m_InitAliens = true;

        for (int i = 0; i < 4; i++)
        {
            m_StateManager->AddShield(std::make_shared<Shield>(glm::vec2(120.0f + (i * 120.0f), 620.0f )));
        }
    }

    void Game::Update(float ts)
    {
        m_Renderer->DrawSprite(*m_Ground, m_GroundTransform);

        if (m_AlienSwarm->CheckWaveComplete())
        {
            m_StateManager->IncrementWave();
            m_AlienSwarm->Init({ GameStateManager::s_GameSpace.x / 7, (GameStateManager::s_GameSpace.y / 4) + (50 * m_StateManager->GetWave()) });
            m_Player->AddLife();
            m_InitAliens = true;
        }

        // Handle projectiles
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
                // Check alien and projectile collision
                m_StopSwarm = m_AlienSwarm->CheckProjectileCollision(*projectile);
                if (projectile->GetDistanceToLive() == 0) continue;
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
                    int livesLeft = m_Player->TakeDamage();
                    m_PlayerHit = true;
                    if (livesLeft == 0)
                    {
                        INFO("Game Over!");
                        m_GameOver = true;
                    }
                }
            }
            // Check shield collision
            if (projectile->GetDistanceToLive() >= 10)
            {
                float shieldCollisionThreshold = (shields[0]->GetPosition().y - shields[0]->GetSize().y / 2) - 10.0f;
                if (projectile->GetPosition().y > shieldCollisionThreshold)
                {
                    for (auto& shield : shields)
                    {
                        glm::vec2 hitPosition = shield->GetHitPosition(projectile->GetPosition().x);
                        if (hitPosition.x > -1 && hitPosition.y > -1 && projectile->GetPosition().y >= shieldCollisionThreshold + hitPosition.y * 2.5f)
                        {
                            shield->TakeDamage(hitPosition);
                            projectile->SetDistanceToLive(0);
                            projectile->CheckForMiss(ts);
                        }
                    }
                }
            }
        }
        m_StateManager->CullProjectiles();

        // Handle when player is hit
        if (m_PlayerHit)
        {
            m_StopSwarm = true;
            if (m_FrameCount % 10 == 0)
                m_Player->Animate("Hit");

            m_PlayerHitTimer -= ts;
            if (!m_GameOver && m_PlayerHitTimer <= 0.0f)
            {
                m_PlayerHit = false;
                m_StopSwarm = false;
                m_PlayerHitTimer = 1.0f;
                m_Player->GetAnimator()->SetActiveSpriteIndex(0);
            }
        }

        // Handle alien animations
        m_AlienSwarm->CheckAnimationsAndCull(ts, [this]() { m_StopSwarm = false; });

        // Handle alien move
        if (!m_InitAliens && !m_StopSwarm && (int)m_GameTimer.elapsedMilliseconds() % (int)((1.0f / m_SwarmFps) * 1000) < (int)(1000 * ts))
            m_AlienSwarm->MoveAliens();

        // Handle player move
        if (m_StateManager->IsMoveValid({ ts * m_MoveVelocity, 0.0f }, m_Player->GetPosition()))
            m_Player->Move({ ts * m_MoveVelocity, 0.0f });

        // Handle drawing
        auto& aliens = m_AlienSwarm->GetAliens();
        if (m_InitAliens)
        {
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
            for (auto& shield : shields)
                m_Renderer->DrawSprite(shield->GetSprite(), shield->GetTransform());
            for (auto& projectile : projectiles)
                m_Renderer->DrawSprite(projectile->GetSprite(), projectile->GetTransform());
            for (auto& alien : aliens)
                m_Renderer->DrawSprite(alien->GetSprite(), alien->GetTransform());
            m_Renderer->DrawSprite(m_Player->GetSprite(), m_Player->GetTransform());
        }

        m_FrameCount++;
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
