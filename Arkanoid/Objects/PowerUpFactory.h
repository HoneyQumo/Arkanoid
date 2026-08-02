#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "Objects/PowerUp.h"

namespace ArkanoidGame
{
    class IPowerUpCommand;

    class PowerUpFactory
    {
    public:
        static std::shared_ptr<PowerUp> TrySpawnAt(sf::Vector2f position);

        static std::shared_ptr<IPowerUpCommand> CreateCommand(PowerUp::Type type);
    };
}
