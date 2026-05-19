#include "Math.h"
#include <random>

namespace ArkanoidGame
{
    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        const sf::Vector2f scale = {desiredWidth / spriteRect.width, desiredHeight / spriteRect.height};
        sprite.setScale(scale);
    }

    void SetOrigin(sf::Sprite& sprite, const sf::Vector2f& origin)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        sprite.setOrigin(origin.x * spriteRect.width, origin.y * spriteRect.height);
    }

    void SetOrigin(sf::RectangleShape& shape, const sf::Vector2f& origin)
    {
        const sf::FloatRect shapeRect = shape.getLocalBounds();
        shape.setOrigin(origin.x * shapeRect.width, origin.y * shapeRect.height);
    }

    sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
    {
        sf::FloatRect textSize = text.getLocalBounds();
        return {
            (textSize.left + textSize.width) * relativePosition.x,
            (textSize.top + textSize.height) * relativePosition.y,
        };
    }

    int GetIntegerInRange(const int a, const int b)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(a, b);
        return dis(gen);
    }
}
