#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    class Collidable
    {
    public:
        virtual ~Collidable() = default;

        virtual bool CheckCollision(std::shared_ptr<Collidable> collidable)
        {
            if (HasCollisionWith(collidable))
            {
                OnHit();
                collidable->OnHit();
                return true;
            }
            return false;
        }

        virtual bool HasCollisionWith(std::shared_ptr<Collidable> collidable) const = 0;

        virtual sf::FloatRect GetBounds() const = 0;

    protected:
        virtual void OnHit() = 0;
    };
}
