#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    class GameObject
    {
    public:
        void Draw(sf::RenderWindow& window) const;

        sf::Sprite& GetSprite();

    protected:
        sf::Sprite _sprite;
    };
}
