#include "Player.h"
#include "SpriteData.h"
#include "Log.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Player::Player()
        : Actor()
    {
        AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::PlayerSprite, SpriteData::LayoutPlayerSprite),
            { SpriteData::SizePlayerSprite[0], SpriteData::SizePlayerSprite[1] }));
        AddSprite(1, Sprite(BinaryTexture::Create(SpriteData::PlayerDeathSprite0, SpriteData::LayoutPlayerDeathSprite0),
            { SpriteData::SizePlayerDeathSprite0[0], SpriteData::SizePlayerDeathSprite0[1] }));
        AddSprite(2, Sprite(BinaryTexture::Create(SpriteData::PlayerDeathSprite1, SpriteData::LayoutPlayerDeathSprite1),
            { SpriteData::SizePlayerDeathSprite1[0], SpriteData::SizePlayerDeathSprite1[1] }));
        m_Laser = new Laser(0, &m_Position, glm::vec2(0.0f, -1.0f));
        m_Laser->SetProjectileSpeed(750.0f);
        m_Animator->CreateAnimation("Hit", [](int activeSprite) { return activeSprite <= 1 ? 2 : 1; });
    }

    Player::~Player()
    {
        delete m_Laser;
    }

    int Player::TakeDamage()
    {
        m_Lives--;
        INFO("You got hit! Lives left: {0}", m_Lives);
        return m_Lives;
    }
}
