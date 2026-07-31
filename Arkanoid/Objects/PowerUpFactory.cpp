#include "Objects/PowerUpFactory.h"

#include <utility>

#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    namespace
    {
        PowerUp::Type GetRandomType()
        {
            static const std::pair<PowerUp::Type, int> weights[] = {
                {PowerUp::Type::Expand, 22},
                {PowerUp::Type::Reduce, 10},
                {PowerUp::Type::MultiBall, 20},
                {PowerUp::Type::Catch, 18},
                {PowerUp::Type::Slow, 18},
                {PowerUp::Type::Life, 12},
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

            return PowerUp::Type::Expand;
        }
    }

    std::shared_ptr<PowerUp> PowerUpFactory::TrySpawnAt(const sf::Vector2f position)
    {
        if (GetIntegerInRange(0, 999) >= static_cast<int>(POWERUP_DROP_CHANCE * 1000.f))
        {
            return nullptr;
        }

        return std::make_shared<PowerUp>(GetRandomType(), position);
    }
}
