#include "Objects/PowerUp.h"

#include "Core/Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    PowerUp::PowerUp(const Type type, const sf::Vector2f position) : _type(type)
    {
        _sprite.setPosition(position);
    }

    void PowerUp::Init(Game& game)
    {
        _sprite.setTexture(game.assets.powerups);
        _sprite.setTextureRect(GetIconRect(_type));
        SetSpriteSize(_sprite, POWERUP_WIDTH, POWERUP_HEIGHT);
        SetSpriteOrigin(_sprite, {0.5f, 0.5f});
    }

    void PowerUp::Update(Game& game, const float dt)
    {
        if (_isCollected) return;

        const auto position = _sprite.getPosition();
        _sprite.setPosition(position.x, position.y + POWERUP_FALL_SPEED * dt);
    }

    bool PowerUp::IsDestroyed() const
    {
        /* Подобранные исчезают сразу, остальные — уйдя за нижний край */
        return _isCollected || _sprite.getPosition().y - POWERUP_HEIGHT > static_cast<float>(SCREEN_HEIGHT);
    }

    bool PowerUp::HasCollisionWith(const Collidable& other) const
    {
        return HasRectRectCollision(GetBounds(), other.GetBounds());
    }

    void PowerUp::OnHit(Collidable&)
    {
        Collect();
    }

    bool PowerUp::IsInstant(const Type type)
    {
        return type == Type::MultiBall || type == Type::Life;
    }

    sf::IntRect PowerUp::GetIconRect(const Type type)
    {
        return {
            static_cast<int>(type) * POWERUP_ICON_WIDTH,
            0,
            POWERUP_ICON_WIDTH,
            POWERUP_ICON_HEIGHT,
        };
    }

    PowerUp::Type PowerUp::GetRandomType()
    {
        /* Полезные бонусы должны выпадать чаще вредного сужения платформы,
           поэтому берём не равномерный выбор, а взвешенный */
        static const std::pair<Type, int> weights[] = {
            {Type::Expand, 22},
            {Type::Reduce, 10},
            {Type::MultiBall, 20},
            {Type::Catch, 18},
            {Type::Slow, 18},
            {Type::Life, 12},
        };

        int total = 0;
        for (const auto& item : weights)
        {
            total += item.second;
        }

        int roll = GetIntegerInRange(0, total - 1);

        for (const auto& item : weights)
        {
            roll -= item.second;
            if (roll < 0) return item.first;
        }

        return Type::Expand;
    }
}
