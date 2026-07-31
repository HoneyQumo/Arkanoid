#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "Objects/PowerUp.h"

namespace ArkanoidGame
{
    class PowerUpFactory
    {
    public:
        /* Бросает кубик на шанс дропа и выбирает тип по весам. nullptr — бонус не выпал */
        static std::shared_ptr<PowerUp> TrySpawnAt(sf::Vector2f position);
    };
}
