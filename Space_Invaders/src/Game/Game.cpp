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
        : m_Shader(nullptr), m_Renderer(nullptr), m_Player(nullptr), m_AlienSwarm(nullptr), m_GameUtils(nullptr), m_Ground(nullptr), m_GroundTransform(glm::mat4(1.0f))
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
        m_GameUtils = std::make_shared<GameUtils>();

        glm::mat4 proj = glm::ortho(0.0f, m_GameUtils->GetGameSpace().x, m_GameUtils->GetGameSpace().y, 0.0f, -1.0f, 1.0f);
        m_Shader = new Shader("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Projection", proj);
        m_Shader->SetUniform2f("u_WindowLayout", windowLayout[0], windowLayout[1]);
        m_Renderer = new SpriteRenderer(*m_Shader);

        std::srand(std::time(0));

        m_Ground = new Sprite(BinaryTexture::Create(SpriteData::GroundSprite, SpriteData::LayoutGroundSprite), { 0.0f, 0.0f });
        m_GroundTransform = glm::translate(glm::mat4(1.0f), { m_GameUtils->GetGameSpace().x / 2, m_GameUtils->GetGameSpace().y - m_GameUtils->GetMargin().y, -1.0f }) *
            glm::scale(glm::mat4(1.0f), { m_GameUtils->GetGameSpace().x, 2.0f, 1.0f });

        m_Player = new Player();
        m_Player->SetPosition({ 300.0f, 685.0f });

        m_AlienSwarm = new AlienSwarm(m_GameUtils);
        m_AlienSwarm->Init({ m_GameUtils->GetGameSpace().x / 7, m_GameUtils->GetGameSpace().y / 4 });
        m_InitAliens = true;
    }

    void Game::Update(float ts)
    {
        m_Renderer->DrawSprite(*m_Ground, m_GroundTransform);

        if (m_AlienSwarm->CheckWaveComplete())
        {
            m_Wave++;
            m_AlienSwarm->Init({ m_GameUtils->GetGameSpace().x / 7, (m_GameUtils->GetGameSpace().y / 4) + (50 * m_Wave) });
            m_Player->AddLife();
            m_InitAliens = true;
        }

        // Handle player projectiles
        auto playerProjectiles = m_Player->GetLaser().GetProjectiles();
        for (auto &projectile : *playerProjectiles)
        {
            if (m_PlayerHit)
                projectile.SetDistanceToLive(0);
            projectile.Move(ts * projectile.GetSpeed() * m_Player->GetLaser().GetDirection());
            m_StopSwarm = m_AlienSwarm->CheckProjectileCollision(projectile);
            projectile.CheckForMiss(ts);
            m_Renderer->DrawSprite(projectile.GetSprite(), projectile.GetTransform());
        }
        m_Player->GetLaser().CullProjectiles();

        // Handle alien projectiles
        auto alienProjectiles = m_AlienSwarm->UpdateProjectiles(ts);
        for (auto projectile : alienProjectiles)
        {
            if (m_PlayerHit)
                projectile->SetDistanceToLive(0);
            projectile->CheckForMiss(ts);
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
            m_Renderer->DrawSprite(projectile->GetSprite(), projectile->GetTransform());
        }
        m_AlienSwarm->CullProjectiles();

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
        if (m_GameUtils->IsMoveValid({ ts * m_MoveVelocity, 0.0f }, m_Player->GetPosition()))
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
                        m_Player->Shoot(m_Player->GetPosition().y - m_GameUtils->GetMargin().x);
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
