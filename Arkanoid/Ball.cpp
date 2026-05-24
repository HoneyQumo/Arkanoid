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

    void Ball::Update(const Platform& platform, const float dt)
    {
        if (_attached)
        {
            const auto platformShape = platform.GetShape();
            const auto platformPosition = platformShape.getPosition();
            const auto platformBounds = platformShape.getLocalBounds();

            _shape.setPosition({
                platformPosition.x,
                platformPosition.y - platformBounds.height,
            });

            _lastBouncedPosition = _shape.getPosition();
            return;
        }

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

    void Ball::SetAttached(const bool& value)
    {
        _attached = value;
    }

    bool Ball::GetAttached() const
    {
        return _attached;
    }

    void Ball::SetVelocity(const sf::Vector2f value)
    {
        _velocity = value;
    }

    sf::Vector2f& Ball::GetVelocity()
    {
        return _velocity;
    }

    void Ball::BounceOffPlatform(const Platform& platform, const float speed)
    {
        const auto& platformShape = platform.GetShape();
        const sf::Vector2f pPosition = platformShape.getPosition();
        const sf::Vector2f bPosition = _shape.getPosition();
        _lastBouncedPosition = bPosition;

        const float halfW = platformShape.getSize().x * 0.5f;
        float hit = (bPosition.x - pPosition.x) / halfW;
        hit = std::max(-1.f, std::min(hit, 1.f));

        /* TODO: Тут меняется скорость полёта ball, нужно нормализовать? */
        _velocity = {speed * hit, -speed};
    }

    /* Todo: Криво рассчитываются углы отскока от стенок */
    void Ball::BounceOffWall(const float speed)
    {
        const auto& position = _shape.getPosition();
        const auto& bounds = _shape.getGlobalBounds();

        const auto top = bounds.top;
        const auto bottom = bounds.top + bounds.height;
        const auto left = bounds.left;
        const auto right = bounds.left + bounds.width;

        const bool topWallCollision = top <= 0.f;
        const bool rightWallCollision = right >= SCREEN_WIDTH;
        const bool bottomWallCollision = bottom >= SCREEN_HEIGHT;
        const bool leftWallCollision = left <= 0.f;

        if (topWallCollision)
        {
            const auto diffX = position.x - _lastBouncedPosition.x;
            _velocity = {speed * Sign(diffX), speed};

            _lastBouncedPosition = position;
        }

        if (rightWallCollision)
        {
            const auto diffY = position.y - _lastBouncedPosition.y;
            _velocity = {-speed, speed * Sign(diffY)};

            _lastBouncedPosition = position;
        }

        if (bottomWallCollision)
        {
            Game& game = Application::Instance().GetGame();
            game.PushState(Game::State::GameOver);
        }

        if (leftWallCollision)
        {
            const auto diffY = position.y - _lastBouncedPosition.y;
            _velocity = {speed, speed * Sign(diffY)};

            _lastBouncedPosition = position;
        }
    }
}
