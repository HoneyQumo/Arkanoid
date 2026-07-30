#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    class Collidable
    {
    public:
        virtual ~Collidable() = default;

        virtual bool CheckCollision(Collidable& other)
        {
            if (HasCollisionWith(other))
            {
                OnHit(other);
                other.OnHit(*this);
                return true;
            }
            return false;
        }

        virtual bool HasCollisionWith(const Collidable& other) const = 0;

        virtual sf::FloatRect GetBounds() const = 0;

    protected:
        virtual void OnHit(Collidable& other) = 0;
    };
}
