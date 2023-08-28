#pragma once
#include "BinaryTexture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>

namespace SpaceInvaders
{
	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(std::shared_ptr<BinaryTexture> texture);
		~Sprite();

		BinaryTexture& GetTexture() { return *m_Texture; }
		VertexArray& GetVAO() { return *m_VAO; }
		IndexBuffer& GetIBO() { return *m_IBO; }

	private:
		std::shared_ptr<BinaryTexture> m_Texture;
		std::shared_ptr<VertexArray> m_VAO;
		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_IBO;
	};
}

