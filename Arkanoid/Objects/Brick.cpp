#include "Objects/Brick.h"

#include <cassert>

#include "Core/Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    Brick::Brick(const Color color, const sf::Vector2f position)
        : _color(color)
    {
        _sprite.setPosition(position);
    }

    void Brick::Init(Game& game)
    {
        _sprite.setTexture(game.assets.atlas);
        _sprite.setTextureRect(GetIdleRect());
        SetSpriteSize(_sprite, BRICK_WIDTH, BRICK_HEIGHT);
        SetSpriteOrigin(_sprite, {0.f, 0.f});
    }

    void Brick::Update(Game& game, float dt)
    {
        if (!_isBreaking) return;

        _breakTimer += dt;
        const int frame = static_cast<int>(_breakTimer / BRICK_DESTROY_FRAME_DURATION);

        if (frame < BRICK_FRAME_COUNT)
        {
            _sprite.setTextureRect(GetBrickFrameRect(_color, frame));
        }
    }

    bool Brick::CheckCollision(Collidable& other)
    {
        if (_isBreaking) return false;

        return Collidable::CheckCollision(other);
    }

    bool Brick::HasCollisionWith(const Collidable& other) const
    {
        return HasRectCircleCollision(GetBounds(), other.GetBounds());
    }

    void Brick::OnHit(Collidable&)
    {
        if (_isBreaking) return;

        _isBreaking = true;

        Emit(ObservableEvent::BrickDestroyed);
    }

    bool Brick::IsDestroyed() const
    {
        return _isBreaking && (_breakTimer / BRICK_DESTROY_FRAME_DURATION) >= BRICK_FRAME_COUNT;
    }

    sf::IntRect Brick::GetIdleRect() const
    {
        return GetBrickFrameRect(_color, 0);
    }

    sf::IntRect Brick::GetBrickFrameRect(const Color color, const int frame)
    {
        return {
            BRICK_ATLAS_LEFT + frame * BRICK_FRAME_WIDTH,
            BRICK_ATLAS_TOP + BRICK_COLOR_ROW.at(color) * BRICK_FRAME_HEIGHT,
            BRICK_FRAME_WIDTH,
            BRICK_FRAME_HEIGHT,
        };
    }

    Brick::Color Brick::GetColorByLevelSymbol(const char symbol)
    {
        switch (symbol)
        {
        case 'R': return Color::Red;
        case 'B': return Color::Blue;
        case 'Y': return Color::Yellow;
        case 'G': return Color::Green;
        case 'P': return Color::Purple;
        case 'O': return Color::Orange;

        default:
            {
                assert(false);
                return Color::Red;
            }
        }
    }

    const std::map<Brick::Color, int> Brick::BRICK_COLOR_ROW = {
        {Color::Red, 0},
        {Color::Green, 1},
        {Color::Blue, 2},
        {Color::Purple, 3},
        {Color::Yellow, 4},
        {Color::Orange, 5},
    };
}
