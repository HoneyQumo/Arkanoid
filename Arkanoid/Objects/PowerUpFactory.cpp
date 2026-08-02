#include "Objects/PowerUpFactory.h"

#include <cassert>
#include <utility>

#include "Objects/PowerUpCommands.h"
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

        const auto type = GetRandomType();

        return std::make_shared<PowerUp>(type, CreateCommand(type), position);
    }

    std::shared_ptr<IPowerUpCommand> PowerUpFactory::CreateCommand(const PowerUp::Type type)
    {
        switch (type)
        {
        case PowerUp::Type::Expand: return std::make_shared<ExpandPlatformCommand>();
        case PowerUp::Type::Reduce: return std::make_shared<ReducePlatformCommand>();
        case PowerUp::Type::Catch: return std::make_shared<StickyPlatformCommand>();
        case PowerUp::Type::Slow: return std::make_shared<SlowBallCommand>();
        case PowerUp::Type::MultiBall: return std::make_shared<MultiBallCommand>();
        case PowerUp::Type::Life: return std::make_shared<ExtraLifeCommand>();

        default:
            {
                assert(false);
                return std::make_shared<ExpandPlatformCommand>();
            }
        }
    }
}
