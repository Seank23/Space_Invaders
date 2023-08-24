#include "Alien.h"
#include "glm/gtc/matrix_transform.hpp"

namespace SpaceInvaders
{
    Alien::Alien(glm::vec2 size)
        : Actor(size)
    {

    }

    Alien::~Alien()
    {

    }

    Sprite& Alien::GetSprite(int animationTime)
    {
        if (animationTime % 2000 <= 1000)
            return m_Sprites[0];
        else
            return m_Sprites[1];
    }
}
