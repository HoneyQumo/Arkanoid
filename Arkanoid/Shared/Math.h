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

    bool HasRectCircleCollision(const sf::FloatRect& rectangle, const sf::FloatRect& circleBounds);

    bool HasRectRectCollision(const sf::FloatRect& first, const sf::FloatRect& second);

    sf::Vector2f RotateVector(const sf::Vector2f& value, float radians);
}
