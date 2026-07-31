#pragma once
#include "Objects/Brick.h"

namespace ArkanoidGame
{
    class ArmoredBrick : public Brick
    {
    public:
        explicit ArmoredBrick(sf::Vector2f position);

    protected:
        void OnHit(Collidable& other) override;
        sf::IntRect GetIdleRect() const override;

    private:
        unsigned _hitPoints;
    };
}
