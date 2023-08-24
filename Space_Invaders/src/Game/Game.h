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
		std::shared_ptr<Actor> m_Player;
		std::vector<Alien> m_Aliens;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<SpriteRenderer> m_Renderer;

		Timer m_GameTimer;

		int m_WindowWidth = 0, m_WindowHeight = 0;
		int m_EdgeBuffer = 50;

		int m_AlienCount[2] = { 11, 5 };
		float m_MoveVelocity = 0.0f;
	};
}

