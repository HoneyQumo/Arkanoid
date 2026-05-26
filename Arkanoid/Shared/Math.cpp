#include "Math.h"
#include <random>

namespace ArkanoidGame
{
    // void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
    // {
    //     const sf::FloatRect spriteRect = sprite.getLocalBounds();
    //     const sf::Vector2f scale = {desiredWidth / spriteRect.width, desiredHeight / spriteRect.height};
    //     sprite.setScale(scale);
    // }

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

    // void SetSpriteOrigin(sf::Sprite& sprite, const sf::Vector2f& origin)
    // {
    //     const sf::FloatRect spriteRect = sprite.getLocalBounds();
    //     sprite.setOrigin(origin.x * spriteRect.width, origin.y * spriteRect.height);
    // }

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

    bool HasRectCircleCollision(const sf::Sprite& rectangle, const sf::Sprite& circle)
    {
        const auto rBounds = rectangle.getGlobalBounds();
        const auto cPosition = circle.getPosition();
        const auto cRadius = circle.getGlobalBounds().width / 2.f;

        const auto& plLeft = rBounds.left;
        const auto& plTop = rBounds.top;
        const auto& plRight = rBounds.left + rBounds.width;
        const auto& plBottom = rBounds.top + rBounds.height;

        const float closestX = std::max(plLeft, std::min(cPosition.x, plRight));
        const float closestY = std::max(plTop, std::min(cPosition.y, plBottom));

        const float dx = cPosition.x - closestX;
        const float dy = cPosition.y - closestY;

        return (dx * dx + dy * dy) <= (cRadius * cRadius);
    }
}
