#include "Objects/BrickFactory.h"

#include "Objects/ArmoredBrick.h"
#include "Objects/UnbreakableBrick.h"

namespace ArkanoidGame
{
    std::shared_ptr<Brick> BrickFactory::CreateBySymbol(const char symbol, const sf::Vector2f position)
    {
        switch (symbol)
        {
        case 'A': return std::make_shared<ArmoredBrick>(position);
        case 'X': return std::make_shared<UnbreakableBrick>(position);
        default: return std::make_shared<Brick>(Brick::GetColorByLevelSymbol(symbol), position);
        }
    }
}
