#include "Ball.h"

#include "Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    Ball::Ball()
    {
        InitShape();
    }

    void Ball::Launch()
    {
        const Game& game = Application::Instance().GetGame();
        const auto& difficultyValues = game.difficulty.GetValues();

        _attached = false;
        _velocity = {0.f * difficultyValues.speed, -1.f * difficultyValues.speed};
    }

    void Ball::Update(const float dt)
    {
        if (_attached) return;

        sf::Vector2f newPosition = _shape.getPosition();
        newPosition += _velocity * dt;
        _shape.setPosition(newPosition);
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

    sf::CircleShape& Ball::GetShape()
    {
        return _shape;
    }

    bool Ball::GetAttached() const
    {
        return _attached;
    }
}
