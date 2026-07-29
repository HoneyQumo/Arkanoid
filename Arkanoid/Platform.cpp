#include "Platform.h"
#include "Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    void Platform::Init(Game& game)
    {
        _sprite = sf::Sprite(game.assets.atlas);
        _sprite.setTextureRect({32, 64, 48, 14});
        SetSpriteSize(_sprite, PLATFORM_WIDTH, PLATFORM_HEIGHT);
        SetSpriteOrigin(_sprite, {0.5f, 0.5f});
        _sprite.setPosition(SCREEN_WIDTH / 2.f, PLATFORM_Y_POSITION);
    }

    void Platform::Update(Game& game, const float dt)
    {
    }

    void Platform::Control(Ball& ball, const float dt)
    {
        const bool& isRMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
        Application::Instance().GetWindow().setMouseCursorVisible(!isRMBPressed);

        if (isRMBPressed)
        {
            const auto position = _sprite.getPosition();
            float mousePositionX = static_cast<float>(sf::Mouse::getPosition(Application::Instance().GetWindow()).x);
            const auto platformHalfW = _sprite.getGlobalBounds().width / 2.f;

            if (mousePositionX - platformHalfW < 0.f)
            {
                mousePositionX = platformHalfW;
            }
            else if (mousePositionX + platformHalfW > static_cast<float>(SCREEN_WIDTH))
            {
                mousePositionX = static_cast<float>(SCREEN_WIDTH) - platformHalfW;
            }

            _sprite.setPosition(mousePositionX, position.y);
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                const auto position = _sprite.getPosition();
                _sprite.setPosition(position.x + (dt * PLATFORM_SPEED), position.y);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                const auto position = _sprite.getPosition();
                _sprite.setPosition(position.x - (dt * PLATFORM_SPEED), position.y);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (_sticky)
            {
                _sticky = false;
                ball.Launch();
            }
        }
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
