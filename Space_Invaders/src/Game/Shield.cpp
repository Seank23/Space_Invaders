#include "Shield.h"
#include "SpriteData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Shield::Shield(glm::vec2 position)
        : Actor()
    {
        glm::vec2 size = { SpriteData::SizeShieldSprite[0], SpriteData::SizeShieldSprite[1] };
        m_Sprite = Sprite(BinaryTexture::Create(SpriteData::ShieldSprite, SpriteData::LayoutShieldSprite), size);
        m_Position = position;
        m_Transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    }

    Shield::~Shield()
    {

    }
}
