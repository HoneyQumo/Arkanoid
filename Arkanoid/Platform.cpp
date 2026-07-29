#include "Platform.h"
#include <algorithm>
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

    void Platform::Control(const float dt)
    {
        auto& window = Application::Instance().GetWindow();

        const bool isRMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

        window.setMouseCursorVisible(!isRMBPressed);
        window.setMouseCursorGrabbed(isRMBPressed);

        const float halfWidth = _sprite.getGlobalBounds().width / 2.f;
        const auto position = _sprite.getPosition();
        float positionX = position.x;

        if (isRMBPressed)
        {
            const float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);

            float ratio = mouseX / static_cast<float>(SCREEN_WIDTH);
            ratio = std::max(0.f, std::min(ratio, 1.f));
            positionX = halfWidth + ratio * (static_cast<float>(SCREEN_WIDTH) - 2.f * halfWidth);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            positionX += dt * PLATFORM_SPEED;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            positionX -= dt * PLATFORM_SPEED;
        }

        positionX = std::max(halfWidth, std::min(positionX, static_cast<float>(SCREEN_WIDTH) - halfWidth));

        _sprite.setPosition(positionX, position.y);
    }

    void Platform::SetWidth(const float width)
    {
        SetSpriteSize(_sprite, width, PLATFORM_HEIGHT);
        SetSpriteOrigin(_sprite, {0.5f, 0.5f});
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
