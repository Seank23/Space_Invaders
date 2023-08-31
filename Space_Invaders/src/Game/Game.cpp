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
        : m_Shader(nullptr), m_Renderer(nullptr), m_Player(nullptr), m_AlienSwarm(nullptr), m_GameUtils(nullptr)
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
        glm::mat4 proj = glm::ortho(0.0f, m_GameWidth, m_GameHeight, 0.0f, -1.0f, 1.0f);
        m_Shader = new Shader("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Projection", proj);
        m_Shader->SetUniform2f("u_WindowLayout", windowLayout[0], windowLayout[1]);
        m_Renderer = new SpriteRenderer(*m_Shader);

        std::srand(std::time(0));

        m_GameUtils = std::make_shared<GameUtils>(glm::vec2(m_GameWidth, m_GameHeight), m_EdgeBuffer);

        m_Player = new Player({ SpriteData::SizePlayerSprite[0], SpriteData::SizePlayerSprite[1] });
        m_Player->SetPosition({ 300.0f, 685.0f });

        m_AlienSwarm = new AlienSwarm(m_GameUtils);
        m_AlienSwarm->Init({ m_GameWidth / 7, m_GameHeight / 4 });
    }

    void Game::Update(float ts)
    {
        if (m_GameOver) return;

        // Handle player projectiles
        auto playerProjectiles = m_Player->GetLaser().GetProjectiles();
        for (auto &projectile : *playerProjectiles)
        {
            projectile.Move(ts * projectile.GetSpeed() * m_Player->GetLaser().GetDirection());
            m_StopSwarm = m_AlienSwarm->CheckProjectileCollision(projectile);

            m_Renderer->DrawSprite(projectile.GetSprite(), projectile.GetTransform());
        }
        m_Player->GetLaser().CullProjectiles();

        // Handle alien projectiles
        auto alienProjectiles = m_AlienSwarm->UpdateProjectiles(ts);
        for (auto projectile : alienProjectiles)
        {
            if (projectile->HasCollided(*m_Player))
            {
                projectile->SetDistanceToLive(0);
                int livesLeft = m_Player->TakeDamage();
                if (livesLeft == 0)
                {
                    INFO("Game Over!");
                    m_GameOver = true;
                }
            }
            m_Renderer->DrawSprite(projectile->GetSprite(), projectile->GetTransform());
        }
        m_AlienSwarm->CullProjectiles();

        // Handle alien animations
        m_AlienSwarm->CheckAnimationsAndCull(ts, [this]() { m_StopSwarm = false; });

        // Handle alien move
        if (!m_StopSwarm && (int)m_GameTimer.elapsedMilliseconds() % (int)((1.0f / m_SwarmFps) * 1000) < (int)(1000 * ts))
            m_AlienSwarm->MoveAliens();

        // Handle player move
        if (m_GameUtils->IsMoveValid({ ts * m_MoveVelocity, 0.0f }, m_Player->GetPosition()))
            m_Player->Move({ ts * m_MoveVelocity, 0.0f });

        // Handle drawing
        auto& aliens = m_AlienSwarm->GetAliens();
        for (auto& alien : aliens)
            m_Renderer->DrawSprite(alien->GetSprite(), alien->GetTransform());
        m_Renderer->DrawSprite(m_Player->GetSprite(), m_Player->GetTransform());
    }

    void Game::InputListener(int key, int action)
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
                    m_Player->Shoot(m_GameHeight);
                    m_LastShootMs = (int)m_GameTimer.elapsedMilliseconds();
                }
            }
        }
    }
}
