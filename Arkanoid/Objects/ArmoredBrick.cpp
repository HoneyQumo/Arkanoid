#include "Objects/ArmoredBrick.h"
#include "Shared/Constants.h"

namespace ArkanoidGame
{
    ArmoredBrick::ArmoredBrick(const sf::Vector2f position)
        : Brick(Color::Orange, position), _hitPoints(BRICK_ARMORED_HIT_POINTS)
    {
    }

    void ArmoredBrick::OnHit(Collidable& other)
    {
        if (IsBreaking()) return;

        if (_hitPoints > 1)
        {
            --_hitPoints;
            _sprite.setTextureRect(GetIdleRect());
            return;
        }

        /* Броня кончилась — ломаемся как обычный кирпич */
        Brick::OnHit(other);
    }

    sf::IntRect ArmoredBrick::GetIdleRect() const
    {
        if (_hitPoints >= 3) return BRICK_TILE_STONE;
        if (_hitPoints == 2) return BRICK_TILE_MASONRY;
        return BRICK_TILE_WOOD;
    }
}
