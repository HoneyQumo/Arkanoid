#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Direction.h"

namespace ArkanoidGame
{
    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

    void SetOrigin(sf::Sprite& sprite, const sf::Vector2f& origin);
    void SetOrigin(sf::RectangleShape& shape, const sf::Vector2f& origin);

    sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

    int GetIntegerInRange(int a, int b);
}
