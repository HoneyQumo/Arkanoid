#include "Brick.h"

#include <cassert>

#include "Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    Brick::Brick(const Kind kind, const Color color, const sf::Vector2f position)
        : _kind(kind), _color(color)
    {
        _hitPoints = kind == Kind::Armored ? BRICK_ARMORED_HIT_POINTS : 1;
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
            const Color debrisColor = _kind == Kind::Colored ? _color : Color::Orange;
            _sprite.setTextureRect(GetBrickFrameRect(debrisColor, frame));
        }
    }

    bool Brick::Hit()
    {
        if (_kind == Kind::Unbreakable || _isBreaking)
        {
            return false;
        }

        if (_hitPoints > 1)
        {
            --_hitPoints;
            _sprite.setTextureRect(GetIdleRect());
            return false;
        }

        _hitPoints = 0;
        _isBreaking = true;
        return true;
    }

    bool Brick::IsDestroyed() const
    {
        return _isBreaking && (_breakTimer / BRICK_DESTROY_FRAME_DURATION) >= BRICK_FRAME_COUNT;
    }

    sf::IntRect Brick::GetIdleRect() const
    {
        switch (_kind)
        {
        case Kind::Unbreakable:
            return BRICK_TILE_DARK_STONE;

        case Kind::Armored:
            {
                if (_hitPoints >= 3) return BRICK_TILE_STONE;
                if (_hitPoints == 2) return BRICK_TILE_MASONRY;
                return BRICK_TILE_WOOD;
            }

        case Kind::Colored:
        default:
            return GetBrickFrameRect(_color, 0);
        }
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

    Brick::Kind Brick::GetKindByLevelSymbol(const char symbol)
    {
        switch (symbol)
        {
        case 'A': return Kind::Armored;
        case 'X': return Kind::Unbreakable;
        default: return Kind::Colored;
        }
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

        /* У особых кирпичей цвет не используется, но конструктор его требует */
        case 'A':
        case 'X':
            return Color::Orange;

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
