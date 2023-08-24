#pragma once
#include <cstdint>

namespace SpaceInvaders
{
	class SpriteData
	{
	public:
		static constexpr uint8_t PlayerSprite[11 * 7] = {
				0,0,0,0,0,1,0,0,0,0,0,
				0,0,0,0,1,1,1,0,0,0,0,
				0,0,0,0,1,1,1,0,0,0,0,
				0,1,1,1,1,1,1,1,1,1,0,
				1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,
		};
		static constexpr int LayoutPlayerSprite[2] = {11, 7};

		static constexpr uint8_t AlienSprite0A[11 * 8] = {
				0,0,1,0,0,0,0,0,1,0,0,
				0,0,0,1,0,0,0,1,0,0,0,
				0,0,1,1,1,1,1,1,1,0,0,
				0,1,1,0,1,1,1,0,1,1,0,
				1,1,1,1,1,1,1,1,1,1,1,
				1,0,1,1,1,1,1,1,1,0,1,
				1,0,1,0,0,0,0,0,1,0,1,
				0,0,0,1,1,0,1,1,0,0,0
		};
		static constexpr int LayoutAlienSprite0A[2] = { 11, 8 };

		static constexpr uint8_t AlienSprite0B[11 * 8] = {
				0,0,1,0,0,0,0,0,1,0,0,
				1,0,0,1,0,0,0,1,0,0,1,
				1,0,1,1,1,1,1,1,1,0,1,
				1,1,1,0,1,1,1,0,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,
				0,1,1,1,1,1,1,1,1,1,0,
				0,0,1,0,0,0,0,0,1,0,0,
				0,1,0,0,0,0,0,0,0,1,0
		};
		static constexpr int LayoutAlienSprite0B[2] = { 11, 8 };
	};
}