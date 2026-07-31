#include "Objects/UnbreakableBrick.h"
#include "Shared/Constants.h"

namespace ArkanoidGame
{
    UnbreakableBrick::UnbreakableBrick(const sf::Vector2f position)
        : Brick(Color::Orange, position)
    {
    }

    void UnbreakableBrick::OnHit(Collidable&)
    {
    }

    sf::IntRect UnbreakableBrick::GetIdleRect() const
    {
        return BRICK_TILE_DARK_STONE;
    }
}
