#include "Data/DifficultyLevel.h"

namespace ArkanoidGame
{
    void DifficultyLevel::SetDifficultyLevel(const Type& type)
    {
        _type = type;
        _value = _config.at(type);
    }

    DifficultyLevel::Type DifficultyLevel::GetType() const
    {
        return _type;
    }

    DifficultyLevel::Values DifficultyLevel::GetValues() const
    {
        return _config.at(_type);
    }
}
