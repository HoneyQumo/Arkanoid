#include "Data/LevelFactory.h"

#include "Data/Level.h"
#include "Objects/BrickFactory.h"
#include "Shared/Constants.h"

namespace ArkanoidGame
{
    std::vector<std::shared_ptr<GameObject>> LevelFactory::CreateLevelObjects(const DifficultyLevel::Type difficulty, const size_t index)
    {
        const auto& level = GetLevel(difficulty, index);

        std::vector<std::shared_ptr<GameObject>> objects;

        for (size_t row = 0; row < level.grid.size(); ++row)
        {
            for (size_t col = 0; col < level.grid[row].size(); ++col)
            {
                const char symbol = level.grid[row][col];

                if (symbol == '.') continue;

                objects.emplace_back(BrickFactory::CreateBySymbol(
                    symbol,
                    sf::Vector2f(static_cast<float>(col) * BRICK_WIDTH, static_cast<float>(row) * BRICK_HEIGHT)));
            }
        }

        return objects;
    }
}
