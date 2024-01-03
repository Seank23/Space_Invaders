#pragma once
#include "Player.h"
#include "AlienSwarm.h"
#include "Shield.h"
#include "TextSprite.h"
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
		void DrawSprites(float ts);

		float m_SwarmFps = 60.0f;
		int m_FrameCount = 0;

		Shader* m_Shader;
		SpriteRenderer* m_Renderer;
		std::shared_ptr<GameStateManager> m_StateManager;
		Player* m_Player;
		AlienSwarm* m_AlienSwarm;

		Sprite* m_Ground;
		glm::mat4 m_GroundTransform;

		Timer m_GameTimer;
		int m_EdgeBuffer = 35;

		float m_MoveVelocity = 0.0f;

		float m_PlayerShootCooldownMs = 500.0f;
		int m_LastShootMs = 0;

		bool m_StopSwarm = false;
		bool m_GameOver = false;
		bool m_PlayerHit = false;
		float m_PlayerHitTimer = 1.0f;
		float m_GameOverTimer = 3.0f;
		bool m_InitAliens = false;

		std::unique_ptr<TextSprite> m_ScoreLabelText;
		std::unique_ptr<TextSprite> m_Player1ScoreText;
		std::unique_ptr<TextSprite> m_HighScoreText;
		std::unique_ptr<TextSprite> m_LivesText;
		std::unique_ptr<TextSprite> m_LivesLeftIcons;
		std::unique_ptr<TextSprite> m_CreditsText;
		std::unique_ptr<TextSprite> m_GameOverText;
	};
}

