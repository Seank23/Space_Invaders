#include "Player.h"
#include "SpriteData.h"
#include "Log.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Player::Player(glm::vec2 size)
        : Actor(size)
    {
        m_Laser = std::make_shared<Laser>(&m_Position, glm::vec2(0.0f, -1.0f),
            std::make_shared<Sprite>(BinaryTexture::Create(SpriteData::Projectile0, SpriteData::LayoutProjectile0)), glm::vec2(2.0f, 8.0f));
    }

    Player::~Player()
    {

    }
}
