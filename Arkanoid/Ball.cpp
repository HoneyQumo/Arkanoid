#include "Ball.h"
#include "Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"
#include <cmath>

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

    void Ball::Update(Game& game, const float dt)
    {
        sf::Vector2f newPosition = _sprite.getPosition();
        newPosition += _velocity * dt;
        _sprite.setPosition(newPosition);
    }

    void Ball::AttachToPlatform(const Platform& platform)
    {
        const auto platformBounds = platform.GetSprite().getGlobalBounds();

        _sprite.setPosition({
            platformBounds.left + platformBounds.width / 2.f,
            platformBounds.top - platformBounds.height / 2.f,
        });
    }

    bool Ball::IsFallen() const
    {
        return _isFallen;
    }

    void Ball::Respawn()
    {
        _isFallen = false;
        _attached = true;
        _velocity = {0.f, 0.f};
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

        const float halfW = platform.GetSprite().getGlobalBounds().width / 2.f;

        float hit = (bPosition.x - pPosition.x) / halfW;
        hit = std::max(-1.f, std::min(hit, 1.f));

        /* TODO: Тут меняется скорость полёта ball, нужно нормализовать? */
        _velocity = {speed * hit, -speed};

        NormalizeVelocity(speed);
    }

    void Ball::BounceOffWall(const float speed)
    {
        const auto bounds = _sprite.getGlobalBounds();
        const float radiusX = bounds.width * 0.5f;
        const float radiusY = bounds.height * 0.5f;

        sf::Vector2f position = _sprite.getPosition();
        bool bounced = false;

        if (bounds.top < 0.f)
        {
            position.y = radiusY;
            if (_velocity.y < 0.f)
            {
                _velocity.y = -_velocity.y;
            }
            bounced = true;
        }

        if (bounds.left < 0.f)
        {
            position.x = radiusX;
            if (_velocity.x < 0.f)
            {
                _velocity.x = -_velocity.x;
            }
            bounced = true;
        }

        if (bounds.left + bounds.width > static_cast<float>(SCREEN_WIDTH))
        {
            position.x = static_cast<float>(SCREEN_WIDTH) - radiusX;
            if (_velocity.x > 0.f)
            {
                _velocity.x = -_velocity.x;
            }
            bounced = true;
        }

        if (bounds.top + bounds.height > static_cast<float>(SCREEN_HEIGHT))
        {
            _isFallen = true;
            return;
        }

        if (bounced)
        {
            _sprite.setPosition(position);
            NormalizeVelocity(speed);
        }
    }

    void Ball::BounceOffRect(const sf::Sprite& rect)
    {
        const auto ballBounds = _sprite.getGlobalBounds();
        const auto rectBounds = rect.getGlobalBounds();

        const float dx = (ballBounds.left + ballBounds.width / 2.f) - (rectBounds.left + rectBounds.width / 2.f);
        const float dy = (ballBounds.top + ballBounds.height / 2.f) - (rectBounds.top + rectBounds.height / 2.f);

        const float overlapX = (ballBounds.width + rectBounds.width) / 2.f - std::abs(dx);
        const float overlapY = (ballBounds.height + rectBounds.height) / 2.f - std::abs(dy);

        sf::Vector2f position = _sprite.getPosition();

        // боковая грань
        if (overlapX < overlapY)
        {
            if (_velocity.x * dx < 0.f)
            {
                _velocity.x = -_velocity.x;
            }
            position.x += (dx < 0.f ? -overlapX : overlapX);
        }
        // горизонтальная грань
        else
        {
            if (_velocity.y * dy < 0.f)
            {
                _velocity.y = -_velocity.y;
            }
            position.y += (dy < 0.f ? -overlapY : overlapY);
        }

        _sprite.setPosition(position);
    }

    void Ball::NormalizeVelocity(const float speed)
    {
        const float len = std::hypot(_velocity.x, _velocity.y);
        constexpr float kEpsilon = 0.00001f;
        if (len > kEpsilon)
        {
            _velocity *= speed / len;
        }
    }
}
