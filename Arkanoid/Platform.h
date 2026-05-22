#pragma once
#include "SFML/Graphics.hpp"
#include "Shared/Direction.h"

namespace ArkanoidGame
{
    class Ball;

    class Platform
    {
    public:
        Platform();
        // ~Platform();

        void Update(Ball& ball, float dt);
        void Draw(sf::RenderWindow& window) const;

        void Control(Ball& ball, float dt);

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
