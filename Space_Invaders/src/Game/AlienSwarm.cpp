#include "AlienSwarm.h"

namespace SpaceInvaders
{
	AlienSwarm::AlienSwarm(std::shared_ptr<GameUtils> gameUtils)
		: m_GameUtils(gameUtils), m_InitialPosition({ 0.0f, 0.0f })
	{
	}

	AlienSwarm::~AlienSwarm()
	{
		for (int i = 0; i < m_Aliens.size(); i++)
			delete m_Aliens[i];
	}

	void AlienSwarm::Init(glm::vec2 initialPosition)
	{
		m_InitialPosition = initialPosition;
		m_Aliens.clear();
		glm::vec2 gameSpace = m_GameUtils->GetGameSpace();
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

	bool AlienSwarm::CheckProjectileCollision(Projectile& projectile)
	{
		for (auto& alien : m_Aliens)
		{
			if (projectile.HasCollided(*alien))
			{
				alien->TakeDamage();
				projectile.SetDistanceToLive(0);
				return true;
			}
		}
		return false;
	}
	std::vector<Projectile> AlienSwarm::UpdateProjectiles(float ts)
	{
		std::vector<Projectile> projectiles;
		for (auto& alien : m_Aliens)
		{
			auto alienProjectiles = alien->GetLaser().GetProjectiles();
			for (auto& p : *alienProjectiles)
			{
				p.Move(ts * p.GetSpeed() * alien->GetLaser().GetDirection());
				projectiles.push_back(p);
			}
		}
		return projectiles;
	}

	void AlienSwarm::CullProjectiles()
	{
		for (auto& alien : m_Aliens)
			alien->GetLaser().CullProjectiles();
	}

	void AlienSwarm::CheckAnimationsAndCull(float ts, std::function<void()> callback)
	{
		for (auto& alien : m_Aliens)
		{
			std::vector<std::string> expiredAnimations = alien->GetAnimator().UpdateAnimationTimers(ts);
			for (std::string anim : expiredAnimations)
			{
				if (anim == "Killed")
				{
					alien->Destroy();
					callback();
				}
			}
		}
		int removedIndex = CullAliens();
		if (removedIndex > -1 && m_AlienIndex > removedIndex)
			m_AlienIndex--;
	}

	void AlienSwarm::MoveAliens()
	{
		for (int i = 0; i < m_Aliens.size(); i++)
		{
			Alien& alien = *m_Aliens[i];
			if (i == m_AlienIndex)
			{
				alien.Move({ m_AlienDirection * m_AlienStepX, (int)m_AlienShouldDescend * m_AlienStepY });
			}
			if (std::rand() % (int)(1.0f / alien.GetShootChance()) == 0)
				alien.Shoot(m_GameUtils->GetGameSpace().y);
		}
		if (m_AlienIndex == m_Aliens.size() - 1)
		{
			m_AlienShouldDescend = ShouldAliensDescend();
			if (m_AlienShouldDescend)
				m_AlienDirection *= -1;
		}

		m_AlienIndex++;
		m_AlienIndex %= m_Aliens.size();
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
			if (!m_GameUtils->IsMoveValid({ m_AlienDirection * m_AlienStepX, 0.0f }, alien->GetPosition()))
			{
				shouldDescend = true;
				break;
			}
		}
		return shouldDescend;
	}
}
