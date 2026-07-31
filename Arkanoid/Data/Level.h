#pragma once
#include <string>
#include <vector>

#include "Data/DifficultyLevel.h"

namespace ArkanoidGame
{
    struct Level
    {
        std::wstring name;
        std::vector<std::string> grid;
    };

    const Level& GetLevel(DifficultyLevel::Type difficulty, size_t index);
    size_t GetLevelCount(DifficultyLevel::Type difficulty);
}
