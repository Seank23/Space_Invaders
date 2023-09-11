#pragma once
#include "Projectile.h"

#include <memory>
#include <vector>

namespace SpaceInvaders
{
	class GameStateManager
	{
    public:
        GameStateManager(GameStateManager const&) = delete;
        GameStateManager& operator=(GameStateManager const&) = delete;

        static std::shared_ptr<GameStateManager> Instance()
        {
            static std::shared_ptr<GameStateManager> s{ new GameStateManager };
            return s;
        }

    private:
        GameStateManager();


    public:
        void AddProjectile(std::shared_ptr<Projectile> p) { m_Projectiles.push_back(p); }
        std::vector<std::shared_ptr<Projectile>>& GetProjectiles() { return m_Projectiles; }
        void CullProjectiles();

    private:
        std::vector<std::shared_ptr<Projectile>> m_Projectiles;
	};
}

