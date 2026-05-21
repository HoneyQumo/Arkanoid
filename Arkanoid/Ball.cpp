#include "Ball.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    Ball::Ball()
    {
        InitShape();
    }

    void Ball::Draw(sf::RenderWindow& window) const
    {
        window.draw(_shape);
    }

    void Ball::InitShape()
    {
        _shape.setRadius(BALL_SIZE / 2.f);
        _shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
        _shape.setFillColor(sf::Color::Blue);
        SetOrigin(_shape, {0.5f, 0.5f});
    }

    sf::CircleShape Ball::GetShape() const
    {
        return _shape;
    }

    sf::Vector2f Ball::GetPosition() const
    {
        return _shape.getPosition();
    }

    void Ball::SetPosition(const sf::Vector2f& position)
    {
        _shape.setPosition(position.x, position.y);
    }
}
