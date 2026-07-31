#pragma once
#include <memory>
#include <vector>

#include "Data/DifficultyLevel.h"
#include "Objects/GameObject.h"

namespace ArkanoidGame
{
    class LevelFactory
    {
    public:
        static std::vector<std::shared_ptr<GameObject>> CreateLevelObjects(
            DifficultyLevel::Type difficulty,
            size_t index);
    };
}
