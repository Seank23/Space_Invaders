#pragma once

#include <memory>

#include "Shader.h"
#include "Sprite.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace SpaceInvaders
{
    class SpriteRenderer
    {
    public:
        SpriteRenderer(Shader& shader);
        ~SpriteRenderer();

        void DrawSprite(Sprite& sprite, glm::mat4 transform);

    private:
        Shader& m_Shader;
    };
}

