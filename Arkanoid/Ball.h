#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    class Ball
    {
    public:
        Ball();

        // void Update();
        void Draw(sf::RenderWindow& window) const;

        void InitShape();
        sf::CircleShape GetShape() const;

        sf::Vector2f GetPosition() const;
        void SetPosition(const sf::Vector2f& position);

    private:
        sf::CircleShape _shape;
    };
}
