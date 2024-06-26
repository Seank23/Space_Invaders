#include "AlienSwarm.h"
#include "Log.h"

#include <iostream>
#include <cmath>

namespace SpaceInvaders
{
	AlienSwarm::AlienSwarm(bool isShip)
		: m_InitialPosition({ 0.0f, 0.0f }), m_StateManager(GameStateManager::Instance()), m_IsShip(isShip)
	{
	}

	AlienSwarm::~AlienSwarm()
	{
		for (int i = 0; i < m_Aliens.size(); i++)
			delete m_Aliens[i];
	}

	void AlienSwarm::Init(glm::vec2 initialPosition)
	{
		m_Aliens.clear();
		m_InitialPosition = initialPosition;
		if (m_IsShip)
		{
			Alien* alien = new Alien(3);
			alien->SetPosition(initialPosition);
			m_Aliens.emplace_back(alien);
		}
		else
		{
			m_AlienIndex = 0;
			glm::vec2 gameSpace = GameStateManager::s_GameSpace;
			m_AlienPaddingX = (gameSpace.x - 2 * m_InitialPosition.x) / (m_AlienCount[0] - 1);
			float yPadding = (gameSpace.y - m_InitialPosition.x - (gameSpace.y / 1.8f)) / m_AlienCount[1];
			int type = 0;
			for (int y = m_AlienCount[1] - 1; y >= 0; y--)
			{
				type = y > 2 ? 2 : y > 0 ? 1 : 0;
				for (int x = 0; x < m_AlienCount[0]; x++)
				{
					Alien* alien = new Alien(type);
					alien->SetPosition({ m_InitialPosition.x + x * m_AlienPaddingX, m_InitialPosition.y + y * yPadding });
					m_Aliens.emplace_back(alien);
				}
			}
		}
	}

	bool AlienSwarm::CheckProjectileCollision(Projectile& projectile)
	{
		for (auto& alien : m_Aliens)
		{
			if (projectile.HasCollided(*alien))
			{
				projectile.SetDistanceToLive(0);
				int livesLeft = alien->TakeDamage();
				if (livesLeft == 0)
				{
					m_StateManager->AddToScore(alien->GetPoints());
					INFO("Score: {0}", m_StateManager->GetScore());
				}
				return true;
			}
		}
		return false;
	}

	void AlienSwarm::CheckAnimationsAndCull(float ts, std::function<void()> callback)
	{
		for (auto& alien : m_Aliens)
		{
			std::vector<std::string> expiredAnimations = alien->GetAnimator()->UpdateAnimationTimers(ts);
			for (std::string anim : expiredAnimations)
			{
				if (anim == "Killed")
				{
					alien->Destroy();
				}
				callback();
			}
		}
		int removedIndex = CullAliens();
		if (removedIndex > -1 && m_AlienIndex > removedIndex)
			m_AlienIndex--;
	}

	void AlienSwarm::MoveAliens()
	{
		if (m_IsShip)
		{
			if (m_Aliens.size() > 0)
			{
				m_Aliens[0]->Move({ -m_AlienStepX * 0.5f, 0.0f });

				if (!m_StateManager->GetAudioHandler().IsClipActive("AlienShip"))
					m_StateManager->GetAudioHandler().PlayClip("AlienShip");	
			}
			else if (m_StateManager->GetAudioHandler().IsClipActive("AlienShip"))
			{
				m_StateManager->GetAudioHandler().StopClip("AlienShip");
			}
		}
		else
		{
			for (int i = 0; i < m_Aliens.size(); i++)
			{
				Alien& alien = *m_Aliens[i];
				if (i == m_AlienIndex)
				{
					alien.Move({ m_AlienDirection * m_AlienStepX, (int)m_AlienShouldDescend * m_AlienStepY });
				}
				if (std::rand() % (int)((1.0f / alien.GetShootChance()) * m_Aliens.size() / (m_StateManager->GetWave() + 1)) == 0)
					alien.Shoot(GameStateManager::s_GameSpace.y - alien.GetPosition().y - GameStateManager::s_Margin.y - 15.0f);
			}
			if (m_AlienIndex == m_Aliens.size() - 1)
			{
				m_AlienShouldDescend = ShouldAliensDescend();
				if (m_AlienShouldDescend)
					m_AlienDirection *= -1;
			}

			if (m_AlienIndex == 0 && !m_IsShip)
			{
				m_StateManager->GetAudioHandler().StopClip("BgNote_" + std::to_string((m_BgNoteIndex - 1) % 4));
				m_StateManager->GetAudioHandler().PlayClip("BgNote_" + std::to_string(m_BgNoteIndex));
				m_BgNoteIndex++;
				m_BgNoteIndex %= 4;
			}
			if (m_Aliens.size() > 0)
			{
				m_AlienIndex++;
				m_AlienIndex %= m_Aliens.size();
			}
		}
	}

	bool AlienSwarm::CheckWaveComplete()
	{
		return m_Aliens.size() == 0;
	}

	bool AlienSwarm::HasReachedGround()
	{
		return m_Aliens[0]->GetPosition().y > m_StateManager->s_GameSpace.y * 0.75f;
	}

	int AlienSwarm::CullAliens()
	{
		int initialSize = m_Aliens.size();
		auto it = std::find_if(m_Aliens.begin(), m_Aliens.end(), [](Alien* a) { return !a->GetIsAlive(); });
		if (it != m_Aliens.end())
		{
			int index = std::distance(m_Aliens.begin(), it);
			m_Aliens.erase(it);
			return index;
		}
		return -1;
	}

	bool AlienSwarm::ShouldAliensDescend()
	{
		bool shouldDescend = false;
		for (auto& alien : m_Aliens)
		{
			if (!m_StateManager->IsMoveValid({ m_AlienDirection * m_AlienStepX, 0.0f }, alien->GetPosition()))
			{
				shouldDescend = true;
				break;
			}
		}
		return shouldDescend;
	}

	void AlienSwarm::CalculateShootChance()
	{
		int playerPosition = m_StateManager->GetPlayerPosition();
		int gameWidth = GameStateManager::s_GameSpace.x;
		for (auto& alien : m_Aliens)
		{
			int posDifference = std::abs(alien->GetPosition().x - playerPosition);
			float lerp = std::lerp(1.0f, 0.03f, (float)posDifference / gameWidth);
			alien->SetShootChance(0.03f * lerp);
		}
	}
}
