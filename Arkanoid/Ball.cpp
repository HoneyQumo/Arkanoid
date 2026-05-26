#include "Ball.h"
#include "Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    void Ball::Init(Game& game)
    {
        _sprite = sf::Sprite(game.assets.atlas);
        _sprite.setTextureRect({32, 32, 16, 16});
        SetSpriteSize(_sprite, BALL_SIZE, BALL_SIZE);
        SetSpriteOrigin(_sprite, {0.5f, 0.5f});
    }

    void Ball::Launch()
    {
        const Game& game = Application::Instance().GetGame();
        const auto& difficultyValues = game.difficulty.GetValues();

        _attached = false;
        _velocity = {0.f * difficultyValues.speed, -1.f * difficultyValues.speed};
    }

    void Ball::Update(Platform& platform, const float dt)
    {
        if (_attached)
        {
            const auto platformSprite = platform.GetSprite();
            const auto platformPosition = platformSprite.getPosition();
            const auto platformBounds = platformSprite.getGlobalBounds();

            _sprite.setPosition({
                platformPosition.x,
                platformPosition.y - platformBounds.height / 2.f,
            });

            _lastBouncedPosition = _sprite.getPosition();
            return;
        }

        sf::Vector2f newPosition = _sprite.getPosition();
        newPosition += _velocity * dt;
        _sprite.setPosition(newPosition);
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

    void Ball::BounceOffPlatform(Platform& platform, const float speed)
    {
        const auto& platformSprite = platform.GetSprite();
        const sf::Vector2f pPosition = platformSprite.getPosition();
        const sf::Vector2f bPosition = _sprite.getPosition();
        _lastBouncedPosition = bPosition;

        // const float halfW = platformSprite.getSize().x * 0.5f;
        constexpr float halfW = PLATFORM_WIDTH / 2.f;
        float hit = (bPosition.x - pPosition.x) / halfW;
        hit = std::max(-1.f, std::min(hit, 1.f));

        /* TODO: Тут меняется скорость полёта ball, нужно нормализовать? */
        _velocity = {speed * hit, -speed};
    }

    /* Todo: Криво рассчитываются углы отскока от стенок */
    void Ball::BounceOffWall(const float speed)
    {
        const auto& position = _sprite.getPosition();
        const auto& bounds = _sprite.getGlobalBounds();

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
