#pragma once
#include "SFML/Graphics.hpp"
#include "Platform.h"

namespace ArkanoidGame
{
    class Ball
    {
    public:
        Ball();

        void Launch();
        void Update(const Platform& platform, float dt);
        void Draw(sf::RenderWindow& window) const;

        void InitShape();
        sf::CircleShape& GetShape();

        void SetAttached(const bool& value);
        bool GetAttached() const;

    private:
        sf::CircleShape _shape;
        sf::Vector2f _velocity{0.f, 0.f};
        bool _attached = true;
    };
}
