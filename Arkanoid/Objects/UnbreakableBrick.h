#pragma once
#include "Objects/Brick.h"

namespace ArkanoidGame
{
    class UnbreakableBrick : public Brick
    {
    public:
        explicit UnbreakableBrick(sf::Vector2f position);

        bool IsUnbreakable() const override { return true; }

    protected:
        void OnHit(Collidable& other) override;
        sf::IntRect GetIdleRect() const override;
    };
}
