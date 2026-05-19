#pragma once
#include "SFML/Graphics.hpp"
#include "Shared/Direction.h"

namespace ArkanoidGame
{
    class Platform
    {
    public:
        Platform();
        // ~Platform();

        void Update(float computedDistance);
        void Draw(sf::RenderWindow& window) const;

        void InitShape();

    private:
        DirectionHorizontal _direction;
        sf::RectangleShape _shape;
    };
}
