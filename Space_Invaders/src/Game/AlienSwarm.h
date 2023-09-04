#pragma once
#include "Alien.h"
#include "GameUtils.h"

#include <vector>
#include <functional>

namespace SpaceInvaders
{
	class AlienSwarm
	{
	public:
		AlienSwarm(std::shared_ptr<GameUtils> gameUtils);
		~AlienSwarm();

		void Init(glm::vec2 initialPosition);

		bool CheckProjectileCollision(Projectile& projectile);
		std::vector<Projectile*> UpdateProjectiles(float ts);
		void CullProjectiles();
		void CheckAnimationsAndCull(float ts, std::function<void()> callback);
		void MoveAliens();
		bool CheckWaveComplete();

		std::vector<Alien*>& GetAliens() { return m_Aliens; }
		void SetAlienIndex(int index) { m_AlienIndex = index; }
		int GetAlienIndex() { return m_AlienIndex; }


	private:
		int CullAliens();
		bool ShouldAliensDescend();

		std::vector<Alien*> m_Aliens;

		int m_AlienCount[2] = { 11, 5 };

		std::shared_ptr<GameUtils> m_GameUtils;
		glm::vec2 m_InitialPosition;

		float m_AlienPaddingX = 0.0f;
		int m_AlienIndex = 0;
		int m_AlienDirection = 1;
		float m_AlienStepX = 6.0f;
		float m_AlienStepY = 20.0f;
		bool m_AlienShouldDescend = false;
	};
}

