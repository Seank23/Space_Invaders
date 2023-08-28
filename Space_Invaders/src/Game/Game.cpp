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
        : m_Shader(nullptr), m_Renderer(nullptr), m_Player(nullptr)
    {
        m_GameTimer.start();
    }

    Game::~Game()
    {
        delete m_Shader;
        delete m_Renderer; 
        delete m_Player;
        for (int i = 0; i < m_Aliens.size(); i++)
            delete m_Aliens[i];
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

        m_Player = new Player({ SpriteData::SizePlayerSprite[0], SpriteData::SizePlayerSprite[1] });
        m_Player->SetSprite(Sprite(BinaryTexture::Create(SpriteData::PlayerSprite, SpriteData::LayoutPlayerSprite)));
        m_Player->SetPosition({ 300.0f, 685.0f });

        glm::vec2 initialPos = { m_GameWidth / 7, m_GameHeight / 4 };

        float xPadding = (m_GameWidth - 2 * initialPos.x) / (m_AlienCount[0] - 1);
        float yPadding = (m_GameHeight - initialPos.x - (m_GameHeight / 1.8f)) / m_AlienCount[1];
        int type = 0;
        for (int y = 0; y < m_AlienCount[1]; y++)
        {
            type = y > 2 ? 2 : y > 0 ? 1 : 0;
            for (int x = 0; x < m_AlienCount[0]; x++)
            {
                Alien* alien = new Alien(type);
                alien->SetPosition({ initialPos.x + x * xPadding, initialPos.y + y * yPadding });
                m_Aliens.emplace_back(alien);
            }
        }
        SpriteAnimator animator;
    }

    void Game::Update(float ts)
    {
        auto playerProjectiles = m_Player->GetLaser().GetProjectiles();
        for (auto &projectile : *playerProjectiles)
        {
            projectile.Move(ts * projectile.GetSpeed() * m_Player->GetLaser().GetDirection());
            for (auto& alien : m_Aliens)
            {
                if (projectile.HasCollided(*alien))
                {
                    alien->TakeDamage();
                    projectile.SetDistanceToLive(0);
                }
            }
            m_Renderer->DrawSprite(projectile.GetSprite(), projectile.GetTransform());
        }
        m_Player->GetLaser().CullProjectiles();
        CullAliens();

        for (auto &alien : m_Aliens)
        {
            auto alienProjectiles = alien->GetLaser().GetProjectiles();
            for (auto &projectile : *alienProjectiles)
            {
                projectile.Move(ts * projectile.GetSpeed() * alien->GetLaser().GetDirection());
                if (projectile.HasCollided(*m_Player))
                {
                    m_Player->TakeDamage();
                    projectile.SetDistanceToLive(0);
                }
                m_Renderer->DrawSprite(projectile.GetSprite(), projectile.GetTransform());
            }
            alien->GetLaser().CullProjectiles();
        }

        if (IsMoveValid({ ts * m_MoveVelocity, 0.0f }, m_Player->GetPosition()))
            m_Player->Move({ ts * m_MoveVelocity, 0.0f });

        m_Renderer->DrawSprite(m_Player->GetSprite(), m_Player->GetTransform());
        for (auto& alien : m_Aliens)
        {
            if ((int)m_GameTimer.elapsedMilliseconds() % 1000 <= ts * 1000)
                alien->Animate("Move");
            if (std::rand() % (int)(1.0f / alien->GetShootChance()) == 0)
                alien->Shoot(m_GameHeight);
            m_Renderer->DrawSprite(alien->GetSprite(), alien->GetTransform());
        }
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
            if (action == GLFW_PRESS) m_Player->Shoot(m_GameHeight);
        }
    }

    bool Game::IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition)
    {
        return ((actorPosition.x + moveVelocity.x) >= m_EdgeBuffer && (actorPosition.x + moveVelocity.x) <= m_GameWidth - m_EdgeBuffer) &&
               ((actorPosition.y + moveVelocity.y) >= m_EdgeBuffer && (actorPosition.y + moveVelocity.y) <= m_GameHeight - m_EdgeBuffer);
    }

    void Game::CullAliens()
    {
        m_Aliens.erase(
            std::remove_if(
                m_Aliens.begin(),
                m_Aliens.end(),
                [](Alien* a) { return !a->GetIsAlive(); }
            ),
            m_Aliens.end()
        );
    }
}
