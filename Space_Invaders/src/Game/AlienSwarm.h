#pragma once
#include "Alien.h"

#include <vector>
#include <functional>

namespace SpaceInvaders
{
	class AlienSwarm
	{
	public:
		AlienSwarm(bool isShip = false);
		~AlienSwarm();

		void Init(glm::vec2 initialPosition);

		bool CheckProjectileCollision(Projectile& projectile);
		void CheckAnimationsAndCull(float ts, std::function<void()> callback);
		void MoveAliens();
		bool CheckWaveComplete();
		bool HasReachedGround();
		void CalculateShootChance();

		std::vector<Alien*>& GetAliens() { return m_Aliens; }
		void SetAlienIndex(int index) { m_AlienIndex = index; }
		int GetAlienIndex() { return m_AlienIndex; }
		//const Alien& GetShip() { return &m_Aliens[0]; }

		void StopSwarm() { m_Stop = true; }
		void RestartSwarm() { m_Stop = false; }
		bool IsStopped() { return m_Stop; }


	private:
		int CullAliens();
		bool ShouldAliensDescend();

		std::shared_ptr<GameStateManager> m_StateManager;
		std::vector<Alien*> m_Aliens;

		int m_AlienCount[2] = { 11, 5 };

		glm::vec2 m_InitialPosition;

		float m_AlienPaddingX = 0.0f;
		int m_AlienIndex = 0;
		int m_AlienDirection = 1;
		float m_AlienStepX = 6.0f;
		float m_AlienStepY = 20.0f;
		bool m_AlienShouldDescend = false;
		bool m_IsShip = false;
		bool m_Stop = false;
	};
}

