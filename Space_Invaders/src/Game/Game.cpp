#include "Game.h"
#include "SpriteData.h"
#include "Engine/BinaryTexture.h"
#include "Log.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace SpaceInvaders
{
    Game::Game()
        : m_Player(nullptr), m_Shader(nullptr)
    {
        m_GameTimer.start();
    }

    Game::~Game()
    {

    }

    void Game::Init(int* windowLayout)
    {
        m_WindowWidth = windowLayout[0];
        m_WindowHeight = windowLayout[1];
        glm::mat4 proj = glm::ortho(0.0f, (float)m_WindowWidth, (float)m_WindowHeight, 0.0f, -1.0f, 1.0f);
        m_Shader = std::make_shared<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Projection", proj);
        m_Renderer = std::make_shared<SpriteRenderer>(*m_Shader);

        std::srand(std::time(0));

        m_Player = std::make_shared<Player>(glm::vec2(37.0f, 25.0f));
        m_Player->SetSprite(Sprite(BinaryTexture::Create(SpriteData::PlayerSprite, SpriteData::LayoutPlayerSprite, BinaryTexture::rgbToUint32(0, 216, 32))));
        m_Player->SetPosition({ 400.0f, 520.0f });

        glm::vec2 initialPos = { m_WindowWidth / 7, m_WindowHeight / 6 };
        for (int y = 0; y < m_AlienCount[1]; y++)
        {
            for (int x = 0; x < m_AlienCount[0]; x++)
            {
                glm::vec2 size = { 37.0f, 25.0f };
                glm::vec2 padding = { (size.x / 2) + 38.0f, (size.y / 2) + 38.0f };
                std::shared_ptr<Alien> alien = std::make_shared<Alien>(size);
                auto texture1 = BinaryTexture::Create(SpriteData::AlienSprite0A, SpriteData::LayoutAlienSprite0A, BinaryTexture::rgbToUint32(255, 255, 255));
                auto texture2 = BinaryTexture::Create(SpriteData::AlienSprite0B, SpriteData::LayoutAlienSprite0B, BinaryTexture::rgbToUint32(255, 255, 255));
                alien->SetSprite(Sprite(texture1));
                alien->SetSprite(Sprite(texture2));
                alien->SetPosition({ initialPos.x + x * padding.x, initialPos.y + y * padding.y });
                m_Aliens.push_back(alien);
            }
        }
    }

    void Game::Update(float ts)
    {
        auto playerProjectiles = m_Player->GetLaser()->GetProjectiles();
        for (auto &projectile : playerProjectiles)
        {
            projectile->Move(ts * projectile->GetSpeed() * m_Player->GetLaser()->GetDirection());
            m_Renderer->DrawSprite(projectile->GetSprite(), projectile->GetTransform());
        }
        m_Player->GetLaser()->CullProjectiles();

        for (auto &alien : m_Aliens)
        {
            auto alienProjectiles = alien->GetLaser()->GetProjectiles();
            for (auto &projectile : alienProjectiles)
            {
                projectile->Move(ts * projectile->GetSpeed() * alien->GetLaser()->GetDirection());
                m_Renderer->DrawSprite(projectile->GetSprite(), projectile->GetTransform());
            }
            alien->GetLaser()->CullProjectiles();
        }

        if (IsMoveValid({ ts * m_MoveVelocity, 0.0f }, m_Player->GetPosition()))
            m_Player->Move({ ts * m_MoveVelocity, 0.0f });

        m_Renderer->DrawSprite(m_Player->GetSprite(), m_Player->GetTransform());
        for (auto& alien : m_Aliens)
        {
            if (std::rand() % (int)(1.0f / alien->GetShootChance()) == 0)
                alien->Shoot(m_WindowHeight);
            m_Renderer->DrawSprite(alien->GetSprite((int)m_GameTimer.elapsedMilliseconds()), alien->GetTransform());
        }
    }

    void Game::InputListener(int key, int action)
    {
        switch (key)
        {
        case GLFW_KEY_LEFT:
            if (action == GLFW_PRESS) m_MoveVelocity = -200.0f;
            else if (action == GLFW_RELEASE) m_MoveVelocity = 0.0f;
            break;
        case GLFW_KEY_RIGHT:
            if (action == GLFW_PRESS) m_MoveVelocity = 200.0f;
            else if (action == GLFW_RELEASE) m_MoveVelocity = 0.0f;
            break;
        case GLFW_KEY_UP:
            if (action == GLFW_PRESS) m_Player->Shoot(m_WindowHeight);
        }
    }

    bool Game::IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition)
    {
        return ((actorPosition.x + moveVelocity.x) >= m_EdgeBuffer && (actorPosition.x + moveVelocity.x) <= m_WindowWidth - m_EdgeBuffer) && 
               ((actorPosition.y + moveVelocity.y) >= m_EdgeBuffer && (actorPosition.y + moveVelocity.y) <= m_WindowHeight - m_EdgeBuffer);
    }
}
