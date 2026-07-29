#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Direction.h"

namespace ArkanoidGame
{
    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

    void SetSpriteOrigin(sf::Sprite& sprite, const sf::Vector2f& origin);

    sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

    int GetIntegerInRange(int a, int b);

    bool HasRectCircleCollision(const sf::Sprite& rectangle, const sf::Sprite& circle);

    bool HasRectRectCollision(const sf::Sprite& first, const sf::Sprite& second);

    sf::Vector2f RotateVector(const sf::Vector2f& value, float radians);
}
