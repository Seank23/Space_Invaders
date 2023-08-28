#include "Player.h"
#include "SpriteData.h"
#include "Log.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Player::Player(glm::vec2 size)
        : Actor(size)
    {
        m_Laser = new Laser(&m_Position, glm::vec2(0.0f, -1.0f),
            Sprite(BinaryTexture::Create(SpriteData::Projectile0, SpriteData::LayoutProjectile0)), glm::vec2(2.0f, 12.0f));
        m_Laser->SetProjectileSpeed(750.0f);
    }

    Player::~Player()
    {
        delete m_Laser;
    }

    void Player::TakeDamage()
    {
        m_Lives--;
        INFO("Lives left: {0}", m_Lives);
    }
}
