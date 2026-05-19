#include "Platform.h"

#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    Platform::Platform()
    {
        InitShape();
    }

    void Platform::Update(const float computedDistance)
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

    void Platform::Draw(sf::RenderWindow& window) const
    {
        window.draw(_shape);
    }

    void Platform::InitShape()
    {
        _shape.setSize({PLATFORM_WIDTH, PLATFORM_HEIGHT});
        _shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f);
        _shape.setFillColor(sf::Color::Magenta);
        SetOrigin(_shape, {0.5f, 0.5f});
    }
}
