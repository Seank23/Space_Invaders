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
		static constexpr uint8_t PlayerSpriteEmpty[11 * 7] = {
				0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,
		};
		static constexpr int LayoutPlayerSprite[2] = {11, 7};
		static constexpr float SizePlayerSprite[2] = {34.0f, 24.0f};

		static constexpr uint8_t PlayerDeathSprite0[16 * 8] = {
				0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
				1,0,0,0,0,0,1,0,0,0,0,1,1,0,0,1,
				0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,
				0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,
				0,1,0,0,1,0,1,1,0,0,1,1,0,0,0,1,
				0,0,1,0,0,0,0,1,1,1,0,0,0,1,0,0,
				0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
				0,0,1,1,0,1,1,1,1,1,1,1,0,0,1,0,
		};
		static constexpr int LayoutPlayerDeathSprite0[2] = { 16, 8 };
		static constexpr float SizePlayerDeathSprite0[2] = { 49.0f, 27.0f };

		static constexpr uint8_t PlayerDeathSprite1[15 * 8] = {
				0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
				0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,
				0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,
				1,0,0,0,1,0,1,1,0,1,0,1,0,0,0,
				0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,
				0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,
		};
		static constexpr int LayoutPlayerDeathSprite1[2] = { 15, 8 };
		static constexpr float SizePlayerDeathSprite1[2] = { 46.0f, 27.0f };

		static constexpr uint8_t AlienSprite0A[8 * 8] = {
				0,0,0,1,1,0,0,0,
				0,0,1,1,1,1,0,0,
				0,1,1,1,1,1,1,0,
				1,1,0,1,1,0,1,1,
				1,1,1,1,1,1,1,1,
				0,1,0,1,1,0,1,0,
				1,0,0,0,0,0,0,1,
				0,1,0,0,0,0,1,0,
		};

		static constexpr uint8_t AlienSprite0B[8 * 8] = {
				0,0,0,1,1,0,0,0,
				0,0,1,1,1,1,0,0,
				0,1,1,1,1,1,1,0,
				1,1,0,1,1,0,1,1,
				1,1,1,1,1,1,1,1,
				0,0,1,0,0,1,0,0,
				0,1,0,1,1,0,1,0,
				1,0,1,0,0,1,0,1,
		};
		static constexpr int LayoutAlienSprite0[2] = { 8, 8 };
		static constexpr float SizeAlienSprite0[2] = { 23.0f, 23.0f };

		static constexpr uint8_t AlienSprite1A[11 * 8] = {
				0,0,1,0,0,0,0,0,1,0,0,
				0,0,0,1,0,0,0,1,0,0,0,
				0,0,1,1,1,1,1,1,1,0,0,
				0,1,1,0,1,1,1,0,1,1,0,
				1,1,1,1,1,1,1,1,1,1,1,
				1,0,1,1,1,1,1,1,1,0,1,
				1,0,1,0,0,0,0,0,1,0,1,
				0,0,0,1,1,0,1,1,0,0,0
		};

		static constexpr uint8_t AlienSprite1B[11 * 8] = {
				0,0,1,0,0,0,0,0,1,0,0,
				1,0,0,1,0,0,0,1,0,0,1,
				1,0,1,1,1,1,1,1,1,0,1,
				1,1,1,0,1,1,1,0,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,
				0,1,1,1,1,1,1,1,1,1,0,
				0,0,1,0,0,0,0,0,1,0,0,
				0,1,0,0,0,0,0,0,0,1,0
		};
		static constexpr int LayoutAlienSprite1[2] = { 11, 8 };
		static constexpr float SizeAlienSprite1[2] = { 32.0f, 25.0f };

		static constexpr uint8_t AlienSprite2A[12 * 8] = {
				0,0,0,0,1,1,1,1,0,0,0,0,
				0,1,1,1,1,1,1,1,1,1,1,0,
				1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,0,0,1,1,0,0,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,
				0,0,0,1,1,0,0,1,1,0,0,0,
				0,0,1,1,0,1,1,0,1,1,0,0,
				1,1,0,0,0,0,0,0,0,0,1,1,
		};

		static constexpr uint8_t AlienSprite2B[12 * 8] = {
				0,0,0,0,1,1,1,1,0,0,0,0,
				0,1,1,1,1,1,1,1,1,1,1,0,
				1,1,1,1,1,1,1,1,1,1,1,1,
				1,1,1,0,0,1,1,0,0,1,1,1,
				1,1,1,1,1,1,1,1,1,1,1,1,
				0,0,1,1,1,0,0,1,1,1,0,0,
				0,1,1,0,0,1,1,0,0,1,1,0,
				0,0,1,1,0,0,0,0,1,1,0,0,
		};
		static constexpr int LayoutAlienSprite2[2] = { 12, 8 };
		static constexpr float SizeAlienSprite2[2] = { 33.0f, 25.0f };

		static constexpr uint8_t AlienShipSprite[16 * 7] = {
				0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
				0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,
				0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
				0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0,
				0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
		};
		static constexpr int LayoutAlienShipSprite[2] = { 16, 7 };
		static constexpr float SizeAlienShipSprite[2] = { 48.0f, 22.0f };

		static constexpr uint8_t AlienDeathSprite[13 * 7] = {
				0,1,0,0,1,0,0,0,1,0,0,1,0,
				0,0,1,0,0,1,0,1,0,0,1,0,0,
				0,0,0,1,0,0,0,0,0,1,0,0,0,
				1,1,0,0,0,0,0,0,0,0,0,1,1,
				0,0,0,1,0,0,0,0,0,1,0,0,0,
				0,0,1,0,0,1,0,1,0,0,1,0,0,
				0,1,0,0,1,0,0,0,1,0,0,1,0,
		};
		static constexpr int LayoutAlienDeathSprite[2] = { 13, 7 };
		static constexpr float SizeAlienDeathSprite[2] = { 34.0f, 25.0f };

		static constexpr uint8_t Projectile0[1 * 4] = { 1, 1, 1, 1 };
		static constexpr int LayoutProjectile0[2] = { 1, 4 };

		static constexpr uint8_t Projectile1[6 * 5] = { 
			0, 0, 1, 1, 0, 0,
			1, 1, 1, 1, 1, 1,
			0, 0, 1, 1, 0, 0,
			0, 0, 1, 1, 0, 0,
			0, 0, 1, 1, 0, 0,
		};
		static constexpr int LayoutProjectile1[2] = { 6, 5 };

		static constexpr uint8_t Projectile2[3 * 7] = {
			0, 1, 0,
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			0, 1, 0,
			1, 0, 0,
			0, 1, 0,
		};
		static constexpr int LayoutProjectile2[2] = { 3, 7 };

		static constexpr uint8_t ProjectileExplosionSprite0[8 * 8] = {
				1,0,0,0,1,0,0,1,
				0,0,1,0,0,0,1,0,
				0,1,1,1,1,1,1,0,
				1,1,1,1,1,1,1,1,
				1,1,1,1,1,1,1,1,
				0,1,1,1,1,1,1,0,
				0,0,1,0,0,1,0,0,
				1,0,0,1,0,0,0,1,
		};
		static constexpr int LayoutProjectileExplosionSprite0[2] = { 8, 8 };
		static constexpr float SizeProjectileExplosionSprite0[2] = { 23.0f, 23.0f };

		static constexpr uint8_t ProjectileExplosionSprite1[6 * 7] = {
				0,0,1,0,0,0,
				1,0,0,0,1,0,
				0,0,1,1,0,1,
				0,1,1,1,1,0,
				1,0,1,1,1,0,
				0,1,1,1,1,1,
				1,0,1,1,1,0,
		};
		static constexpr int LayoutProjectileExplosionSprite1[2] = { 6, 7 };
		static constexpr float SizeProjectileExplosionSprite1[2] = { 17.0f, 20.0f };

		static constexpr uint8_t ShieldDamageSprite[6 * 8] = {
				0,0,1,1,0,0,
				1,0,1,1,1,0,
				0,0,1,1,0,1,
				0,1,1,1,1,0,
				1,0,1,1,1,0,
				1,1,1,1,1,1,
				1,0,1,1,1,0,
				0,1,0,1,0,1,
		};
		static constexpr uint8_t ShieldDamageReverseSprite[6 * 8] = {
				0,1,0,1,0,1,
				1,0,1,1,1,0,
				1,1,1,1,1,1,
				1,0,1,1,1,0,
				0,1,1,1,1,0,
				0,0,1,1,0,1,
				1,0,1,1,1,0,
				0,0,1,1,0,0,
		};
		static constexpr int LayoutShieldDamageSprite[2] = { 6, 8 };
		static constexpr float SizeShieldDamageSprite[2] = { 18.0f, 23.0f };

		static constexpr uint8_t GroundSprite[1 * 4] = { 1, 1, 1, 1 };
		static constexpr int LayoutGroundSprite[2] = { 1, 4 };

		static constexpr uint8_t ShieldSprite[19 * 17] = {
			0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
			0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		};
		static constexpr int LayoutShieldSprite[2] = { 19, 17 };
		static constexpr float SizeShieldSprite[2] = { 57.0f, 50.0f };

		static constexpr uint8_t AlienShipScoreSprite[19 * 7] = {
				0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,
				0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,
				0,0,1,0,0,0,0,1,0,0,1,1,0,0,1,0,0,1,1,
				0,0,1,0,0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,
				0,0,1,0,0,0,0,1,1,0,0,1,0,0,1,1,0,0,1,
				0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,
				0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,
		};
		static constexpr int LayoutAlienShipScoreSprite[2] = { 19, 7 };
		static constexpr float SizeAlienShipScoreSprite[2] = { 50.0f, 18.0f };
	};
}
