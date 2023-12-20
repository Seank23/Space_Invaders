#include "TextSprite.h"
#include "TextData.h"
#include "SpriteData.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
	TextSprite::TextSprite(std::string text, glm::vec2 position, glm::vec2 size, const int* layout)
		: m_Text(text), m_Position(position), m_Size(size), m_Layout(layout)
	{
		CreateTextSprite(text, size, layout);
		m_Transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	}

	TextSprite::~TextSprite()
	{
	}

	void TextSprite::SetText(std::string text)
	{
		m_Text = text;
		CreateTextSprite(text, m_Size, m_Layout);
	}

	void TextSprite::SetSize(glm::vec2 size)
	{
		m_Size = size;
		m_Transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	}

	void TextSprite::SetPosition(glm::vec2 position)
	{
		m_Position = position;
		m_Transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { m_Size.x, m_Size.y, 1.0f });
	}

	const uint8_t* TextSprite::GetCharacter(char character)
	{
		switch (character)
		{
		case '0': return TextData::TextChar_0;
		case '1': return TextData::TextChar_1;
		case '2': return TextData::TextChar_2;
		case '3': return TextData::TextChar_3;
		case '4': return TextData::TextChar_4;
		case '5': return TextData::TextChar_5;
		case '6': return TextData::TextChar_6;
		case '7': return TextData::TextChar_7;
		case '8': return TextData::TextChar_8;
		case '9': return TextData::TextChar_9;
		case 's': return TextData::TextChar_S;
		case 'c': return TextData::TextChar_C;
		case 'o': return TextData::TextChar_O;
		case 'r': return TextData::TextChar_R;
		case 'e': return TextData::TextChar_E;
		case 'h': return TextData::TextChar_H;
		case 'i': return TextData::TextChar_I;
		case 'd': return TextData::TextChar_D;
		case 't': return TextData::TextChar_T;
		case '<': return TextData::TextChar_Left;
		case '>': return TextData::TextChar_Right;
		case '-': return TextData::TextChar_Dash;
		case ' ': return TextData::TextChar_Space;
		case '`': return SpriteData::PlayerSprite;
		case '_': return SpriteData::PlayerSpriteEmpty;
		}
		return TextData::TextChar_0;
	}

	void TextSprite::CreateTextSprite(std::string text, glm::vec2 size, const int* layout)
	{
		glm::vec2 charLayout;
		if (layout != nullptr)
			charLayout = { layout[0], layout[1] };
		else
			charLayout = { TextData::LayoutTextChar[0], TextData::LayoutTextChar[1] };
		std::vector<const uint8_t*> chars;
		for (char c : text)
		{
			auto pixels = GetCharacter(c);
			chars.push_back(pixels);
		}
		int charSpacing = 3;
		std::vector<uint8_t> textPixels;
		int textLayout[2] = { chars.size() * (charLayout.x + charSpacing), charLayout.y };
		for (int y = 0; y < charLayout.y; y++)
		{
			for (auto c : chars)
			{
				for (int x = 0; x < charLayout.x; x++)
				{
					int index = (y * charLayout.x) + x;
					textPixels.push_back(c[index]);
				}
				for (int i = 0; i < charSpacing; i++)
					textPixels.push_back(0);
			}
		}
		m_Sprite = Sprite(BinaryTexture::Create(&textPixels[0], textLayout), size);
	}
}
