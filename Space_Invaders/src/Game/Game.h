#pragma once
#include "Player.h"
#include "AlienSwarm.h"
#include "GameUtils.h"
#include "Engine/Shader.h"
#include "Engine/SpriteRenderer.h"
#include "Engine/Timer.h"

#include <memory>

namespace SpaceInvaders
{
	class Game
	{
	public:
		Game();
		~Game();

		void Init(int* windowLayout);
		void Update(float ts);
		void InputListener(int key, int action);

	private:
		float m_GameWidth = 600.0f;
		float m_GameHeight = 800.0f;
		float m_SwarmFps = 60.0f;

		Shader* m_Shader;
		SpriteRenderer* m_Renderer;

		std::shared_ptr<GameUtils> m_GameUtils;
		Player* m_Player;
		AlienSwarm* m_AlienSwarm;

		Timer m_GameTimer;
		int m_EdgeBuffer = 35;

		float m_MoveVelocity = 0.0f;

		float m_PlayerShootCooldownMs = 500.0f;
		int m_LastShootMs = 0;

		bool m_StopSwarm = false;
		bool m_GameOver = false;
	};
}

