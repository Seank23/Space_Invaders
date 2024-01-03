#include "Shield.h"
#include "SpriteData.h"
#include "Log.h"

#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>

namespace SpaceInvaders
{
    Shield::Shield(glm::vec2 position)
        : Actor()
    {
        m_Pixels.assign(SpriteData::ShieldSprite, SpriteData::ShieldSprite + sizeof(SpriteData::ShieldSprite));
        m_Size = { SpriteData::SizeShieldSprite[0], SpriteData::SizeShieldSprite[1] };
        m_SpriteLayout = { SpriteData::LayoutShieldSprite[0], SpriteData::LayoutShieldSprite[1] };
        m_Sprite = Sprite(BinaryTexture::Create(&m_Pixels[0], SpriteData::LayoutShieldSprite), m_Size);
        m_Position = position;
        m_Transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
            * glm::scale(glm::mat4(1.0f), { m_Size.x, m_Size.y, 1.0f });
        CalculateDamageDepth();
    }

    Shield::~Shield()
    {

    }

    glm::vec2 Shield::GetHitPosition(int posX)
    {
        int shieldLeft = m_Position.x - m_Size.x / 2;
        int shieldRight = m_Position.x + m_Size.x / 2;
        if (posX >= shieldLeft && posX <= shieldRight)
        {
            int shieldPos = posX - shieldLeft;
            int pixelIndex = std::floor(shieldPos / (m_Size.x / m_SpriteLayout.x));
            pixelIndex = std::clamp(pixelIndex, 0, (int)m_SpriteLayout.x - 1);

            return { pixelIndex, m_DamageDepth[pixelIndex] };
        }
        else
            return { -1, -1 };
    }

    void Shield::TakeDamage(glm::vec2 position)
    {
        std::vector<uint8_t> explosionPixels(SpriteData::ShieldDamageSprite, SpriteData::ShieldDamageSprite + sizeof(SpriteData::ShieldDamageSprite));
        glm::vec2 layout = { SpriteData::LayoutShieldDamageSprite[0], SpriteData::LayoutShieldDamageSprite[1] };
        SubtractPixels(explosionPixels, layout, position);
        CalculateDamageDepth();
        m_Sprite = Sprite(BinaryTexture::Create(&m_Pixels[0], SpriteData::LayoutShieldSprite), m_Size);
    }

    void Shield::Reset()
    {
        m_Pixels.assign(SpriteData::ShieldSprite, SpriteData::ShieldSprite + sizeof(SpriteData::ShieldSprite));
        m_Sprite = Sprite(BinaryTexture::Create(&m_Pixels[0], SpriteData::LayoutShieldSprite), m_Size);
        CalculateDamageDepth();
    }

    void Shield::SubtractPixels(std::vector<uint8_t> pixels, glm::vec2 layout, glm::vec2 position)
    {
        int pixelsIndex = 0;
        for (int i = 0; i < m_Pixels.size(); i++)
        {
            if (pixelsIndex == pixels.size()) return;

            int row = std::floor(i / m_SpriteLayout.x);
            int col = i % (int)m_SpriteLayout.x;

            if (row == std::clamp(row, (int)position.y, (int)(position.y + layout.y) - 1) && col == std::clamp(col, (int)position.x, (int)(position.x + layout.x) - 1))
            {
                m_Pixels[i] = m_Pixels[i] == 1 && pixels[pixelsIndex] == 0 ? 1 : 0;
                pixelsIndex++;
            }
        }
    }

    void Shield::CalculateDamageDepth()
    {
        m_DamageDepth.clear();
        for (int i = 0; i < m_SpriteLayout.x; i++)
        {
            bool depthHit = false;
            for (int j = 0; j < m_SpriteLayout.y; j++)
            {
                if (m_Pixels[i + j * m_SpriteLayout.x] == 1)
                {
                    m_DamageDepth.push_back(j);
                    depthHit = true;
                    break;
                }
            }
            if (!depthHit) m_DamageDepth.push_back(-1);
        }
    }
}
