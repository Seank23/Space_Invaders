#include "Alien.h"
#include "SpriteData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Alien::Alien(int type)
        : Actor(), m_Type(type), m_Points(0), m_Lives(1)
    {
        m_Laser = new Laser(1, &m_Position, glm::vec2(0.0f, 1.0f));
        m_Laser->SetProjectileSpeed(300.0f);

        switch(type)
        {
        case 0:
            AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::AlienSprite0A, SpriteData::LayoutAlienSprite0),
                { SpriteData::SizeAlienSprite0[0], SpriteData::SizeAlienSprite0[1] }));
            AddSprite(1, Sprite(BinaryTexture::Create(SpriteData::AlienSprite0B, SpriteData::LayoutAlienSprite0),
                { SpriteData::SizeAlienSprite0[0], SpriteData::SizeAlienSprite0[1] }));
            m_Points = 30;
            break;
        case 1:
            AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::AlienSprite1A, SpriteData::LayoutAlienSprite1),
                { SpriteData::SizeAlienSprite1[0], SpriteData::SizeAlienSprite1[1] }));
            AddSprite(1, Sprite(BinaryTexture::Create(SpriteData::AlienSprite1B, SpriteData::LayoutAlienSprite1),
                { SpriteData::SizeAlienSprite1[0], SpriteData::SizeAlienSprite1[1] }));
            m_Points = 20;
            break;
        case 2:
            AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::AlienSprite2A, SpriteData::LayoutAlienSprite2),
                { SpriteData::SizeAlienSprite2[0], SpriteData::SizeAlienSprite2[1] }));
            AddSprite(1, Sprite(BinaryTexture::Create(SpriteData::AlienSprite2B, SpriteData::LayoutAlienSprite2),
                { SpriteData::SizeAlienSprite2[0], SpriteData::SizeAlienSprite2[1] }));
            m_Points = 10;
            break;
        case 3:
            AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::AlienShipSprite, SpriteData::LayoutAlienShipSprite),
                { SpriteData::SizeAlienShipSprite[0], SpriteData::SizeAlienShipSprite[1] }));
            m_Points = 100;
        }
        AddSprite(2, Sprite(BinaryTexture::Create(SpriteData::AlienDeathSprite, SpriteData::LayoutAlienDeathSprite),
            { SpriteData::SizeAlienDeathSprite[0], SpriteData::SizeAlienDeathSprite[1] }));
        if (type == 3)
        {
            AddSprite(3, Sprite(BinaryTexture::Create(SpriteData::AlienShipScoreSprite, SpriteData::LayoutAlienShipScoreSprite),
                { SpriteData::SizeAlienShipScoreSprite[0], SpriteData::SizeAlienShipScoreSprite[1] }));
            m_Animator->CreateAnimation("Explode", [](int activeSprite) { return 2; }, 200, 0);
            m_Animator->CreateAnimation("Killed", [](int activeSprite) { return 3; }, 500, 0);
        }
        else
        {
            m_Animator->CreateAnimation("Killed", [](int activeSprite) { return 2; }, 275, 0);
            m_Animator->CreateAnimation("Move", [](int activeSprite) { return activeSprite == 0 ? 1 : 0; });
        }

}

    Alien::~Alien()
    {
        delete m_Laser;
    }

    void Alien::Move(glm::vec2 position)
    {
        if (m_Type != 3) Animate("Move");
        if (m_Type == 3 && m_Position.x < -50.0f) m_IsAlive = false;
        Actor::Move(position);
    }

    int Alien::TakeDamage()
    {
        m_Lives--;
        if (m_Lives == 0)
            m_Type == 3 ? Animate("Explode") : Animate("Killed");
        return m_Lives;
    }
}
