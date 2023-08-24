#include "SpriteRenderer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
	SpriteRenderer::SpriteRenderer(Shader& shader)
        : m_Shader(shader)
	{
		m_Shader.Bind();
		m_Shader.SetUniform1i("u_Image", 0);
	}

	SpriteRenderer::~SpriteRenderer()
	{

	}

	void SpriteRenderer::DrawSprite(Sprite& sprite, glm::mat4 transform)
	{
        m_Shader.Bind();
        m_Shader.SetUniformMat4f("u_Model", transform);

		sprite.GetTexture().Bind();
        sprite.GetVAO().Bind();
        sprite.GetIBO().Bind();
        glDrawElements(GL_TRIANGLES, sprite.GetIBO().GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
