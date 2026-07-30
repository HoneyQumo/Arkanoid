#include "Math.h"
#include <random>
#include <cmath>

namespace ArkanoidGame
{
    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
    {
        const sf::IntRect& frame = sprite.getTextureRect();
        if (frame.width <= 0 || frame.height <= 0)
        {
            return;
        }

        sprite.setScale({
            desiredWidth / static_cast<float>(frame.width),
            desiredHeight / static_cast<float>(frame.height)
        });
    }

    void SetSpriteOrigin(sf::Sprite& sprite, const sf::Vector2f& origin)
    {
        const sf::IntRect& frame = sprite.getTextureRect();
        sprite.setOrigin(
            origin.x * static_cast<float>(frame.width),
            origin.y * static_cast<float>(frame.height)
        );
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

    bool HasRectCircleCollision(const sf::FloatRect& rectangle, const sf::FloatRect& circleBounds)
    {
        const float cRadius = circleBounds.width / 2.f;
        const sf::Vector2f cPosition{
            circleBounds.left + circleBounds.width / 2.f,
            circleBounds.top + circleBounds.height / 2.f,
        };

        const auto& plLeft = rectangle.left;
        const auto& plTop = rectangle.top;
        const auto plRight = rectangle.left + rectangle.width;
        const auto plBottom = rectangle.top + rectangle.height;

        const float closestX = std::max(plLeft, std::min(cPosition.x, plRight));
        const float closestY = std::max(plTop, std::min(cPosition.y, plBottom));

        const float dx = cPosition.x - closestX;
        const float dy = cPosition.y - closestY;

        return (dx * dx + dy * dy) <= (cRadius * cRadius);
    }

    bool HasRectRectCollision(const sf::FloatRect& first, const sf::FloatRect& second)
    {
        return first.intersects(second);
    }

    sf::Vector2f RotateVector(const sf::Vector2f& value, const float radians)
    {
        const float sin = std::sin(radians);
        const float cos = std::cos(radians);

        return {
            value.x * cos - value.y * sin,
            value.x * sin + value.y * cos,
        };
    }
}
