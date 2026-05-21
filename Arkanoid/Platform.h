#pragma once
#include "Ball.h"
#include "SFML/Graphics.hpp"
#include "Shared/Direction.h"

namespace ArkanoidGame
{
    class Platform
    {
    public:
        Platform();
        // ~Platform();

        void Update(Ball& ball, float computedDistance);
        void Draw(sf::RenderWindow& window) const;

        void Control(Ball& ball, float computedDistance);

        void InitShape();
        sf::RectangleShape GetShape() const;

        void SetSticky(const bool& value);
        bool GetSticky() const;

    private:
        DirectionHorizontal _direction;
        sf::RectangleShape _shape;
        bool _sticky = true;
    };
}
