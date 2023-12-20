#pragma once
#include "pch.h"
#include "Engine/Sprite.h"

#include "glm/glm.hpp"

namespace SpaceInvaders
{
	class TextRenderer
	{
	public:
		TextRenderer(std::string text, glm::vec2 position, glm::vec2 size, const int* layout = nullptr);
		~TextRenderer();

		void SetText(std::string text);
		void SetSize(glm::vec2 size);
		void SetPosition(glm::vec2 position);

		Sprite& GetSprite() { return m_Sprite; }
		glm::mat4& GetTransform() { return m_Transform; }
		std::string GetTextString() { return m_Text; }

	private:
		const uint8_t* GetCharacter(char character);
		void CreateTextSprite(std::string text, glm::vec2 size, const int* layout = nullptr);

		std::string m_Text;
		Sprite m_Sprite;
		glm::vec2 m_Size;
		glm::vec2 m_Position;
		glm::mat4 m_Transform;
		const int* m_Layout;
	};
}

