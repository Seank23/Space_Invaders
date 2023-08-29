#pragma once
#include "Player.h"
#include "Alien.h"
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

		bool IsMoveValid(glm::vec2 moveVelocity, glm::vec2 actorPosition);

	private:
		int CullAliens();

		float m_GameWidth = 600.0f;
		float m_GameHeight = 800.0f;

		Shader* m_Shader;
		SpriteRenderer* m_Renderer;

		Player* m_Player;
		std::vector<Alien*> m_Aliens;

		Timer m_GameTimer;
		int m_EdgeBuffer = 50;

		int m_AlienCount[2] = { 11, 5 };
		float m_MoveVelocity = 0.0f;

		bool m_StopAliens = false;
		float m_AlienPaddingX = 0.0f;
		int m_AlienIndex = 0;
	};
}

