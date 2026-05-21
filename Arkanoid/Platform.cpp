#include "Platform.h"

#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    Platform::Platform()
    {
        InitShape();
    }

    void Platform::Update(Ball& ball, const float computedDistance)
    {
        Control(computedDistance);

        if (_sticky)
        {
            const auto& platformShape = GetShape();
            const auto& platformPosition = platformShape.getPosition();
            const auto& platformBounds = platformShape.getLocalBounds();

            ball.SetPosition({
                platformPosition.x,
                platformPosition.y - platformBounds.height,
            });
        }
    }

    void Platform::Draw(sf::RenderWindow& window) const
    {
        window.draw(_shape);
    }

    void Platform::Control(const float computedDistance)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            const auto position = _shape.getPosition();
            _shape.setPosition(position.x + computedDistance, position.y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            const auto position = _shape.getPosition();
            _shape.setPosition(position.x - computedDistance, position.y);
        }
    }

    void Platform::InitShape()
    {
        _shape.setSize({PLATFORM_WIDTH, PLATFORM_HEIGHT});
        _shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f);
        _shape.setFillColor(sf::Color::Magenta);
        SetOrigin(_shape, {0.5f, 0.5f});
    }

    sf::RectangleShape Platform::GetShape() const
    {
        return _shape;
    }

    void Platform::SetSticky(const bool& value)
    {
        _sticky = value;
    }

    bool Platform::GetSticky() const
    {
        return _sticky;
    }
}
