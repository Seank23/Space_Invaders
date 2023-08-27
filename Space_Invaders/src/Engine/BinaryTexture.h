#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace SpaceInvaders
{
	class BinaryTexture
	{
	public:
		BinaryTexture(const uint8_t* pixels, const int* layout, const uint32_t color);
		~BinaryTexture();

		void Bind(unsigned int slot = 0);
		void Unbind();

		static uint32_t rgbToUint32(uint32_t r, uint32_t g, uint32_t b)
		{
			return (r << 24) | (g << 16) | (b << 8) | 255;
		}

		static std::shared_ptr<BinaryTexture> Create(const uint8_t* pixels, const int* layout, const uint32_t color = 0xFFFFFFFF)
		{
			return std::make_shared<BinaryTexture>(pixels, layout, color);
		}

	private:
		unsigned int m_RendererID;
		const int* m_Layout;
		std::vector<uint32_t> m_Bitmap;
	};
}

