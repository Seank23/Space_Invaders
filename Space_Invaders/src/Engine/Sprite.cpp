#include "Sprite.h"
#include "VertexBufferLayout.h"

namespace SpaceInvaders
{
	Sprite::Sprite(const std::shared_ptr<BinaryTexture> texture, glm::vec2 size)
        : m_Size(size)
	{
        float positions[] =
        {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        m_Texture = texture;
        m_Texture->Bind();
        m_VAO = std::make_shared<VertexArray>();
        m_VBO = std::make_shared<VertexBuffer>(positions, sizeof(positions));
        m_IBO = std::make_shared<IndexBuffer>(indices, 6);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);
        m_VBO->Bind();
        m_VAO->Bind();
	}

	Sprite::~Sprite()
	{

	}
}