#pragma once
#include "BinaryTexture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>
#include <glm/glm.hpp>

namespace SpaceInvaders
{
	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(const std::shared_ptr<BinaryTexture> texture, glm::vec2 size);
		~Sprite();

		glm::vec2 GetSize() { return m_Size; }
		BinaryTexture& GetTexture() { return *m_Texture; }
		VertexArray& GetVAO() { return *m_VAO; }
		IndexBuffer& GetIBO() { return *m_IBO; }

	private:
		glm::vec2 m_Size;
		std::shared_ptr<BinaryTexture> m_Texture;
		std::shared_ptr<VertexArray> m_VAO;
		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_IBO;
	};
}

