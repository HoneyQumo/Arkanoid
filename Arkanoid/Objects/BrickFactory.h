#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "Objects/Brick.h"

namespace ArkanoidGame
{
    class BrickFactory
    {
    public:
        static std::shared_ptr<Brick> CreateBySymbol(char symbol, sf::Vector2f position);
    };
}
