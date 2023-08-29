#include "Alien.h"
#include "SpriteData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Alien::Alien(int type)
        : Actor(), m_Type(type)
    {
        m_Laser = new Laser(&m_Position, glm::vec2(0.0f, 1.0f),
            Sprite(BinaryTexture::Create(SpriteData::Projectile0, SpriteData::LayoutProjectile0)), glm::vec2(2.0f, 20.0f));
        m_Laser->SetProjectileSpeed(400.0f);

        switch(type)
        {
        case 0:
            m_Animator.AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::AlienSprite0A, SpriteData::LayoutAlienSprite0)));
            m_Animator.AddSprite(1, Sprite(BinaryTexture::Create(SpriteData::AlienSprite0B, SpriteData::LayoutAlienSprite0)));
            SetSize({ SpriteData::SizeAlienSprite0[0], SpriteData::SizeAlienSprite0[1] });
            break;
        case 1:
            m_Animator.AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::AlienSprite1A, SpriteData::LayoutAlienSprite1)));
            m_Animator.AddSprite(1, Sprite(BinaryTexture::Create(SpriteData::AlienSprite1B, SpriteData::LayoutAlienSprite1)));
            SetSize({ SpriteData::SizeAlienSprite1[0], SpriteData::SizeAlienSprite1[1] });
            break;
        case 2:
            m_Animator.AddSprite(0, Sprite(BinaryTexture::Create(SpriteData::AlienSprite2A, SpriteData::LayoutAlienSprite2)));
            m_Animator.AddSprite(1, Sprite(BinaryTexture::Create(SpriteData::AlienSprite2B, SpriteData::LayoutAlienSprite2)));
            SetSize({ SpriteData::SizeAlienSprite2[0], SpriteData::SizeAlienSprite2[1] });
            break;
        }
        m_Animator.AddSprite(2, Sprite(BinaryTexture::Create(SpriteData::AlienDeathSprite, SpriteData::LayoutAlienDeathSprite)));
        m_Animator.CreateAnimation("Move", [](int activeSprite) { return activeSprite == 0 ? 1 : 0; }, 0);
    }

    Alien::~Alien()
    {
        delete m_Laser;
    }

    void Alien::Move(glm::vec2 position)
    {
        m_Animator.Animate("Move");
        Actor::Move(position);
    }

    void Alien::TakeDamage()
    {
        m_IsAlive = false;
    }
}
