#pragma once
#include <map>
#include "Shared/Constants.h"

namespace ArkanoidGame
{
    class DifficultyLevel
    {
    public:
        enum class Type
        {
            Easy = 0,
            EasyMedium,
            Medium,
            MediumHard,
            Hard
        };

        struct Values
        {
            float speed;
            unsigned pointsRate;
            unsigned comboBonus;
        };

        using ConfigMap = std::map<Type, Values>;

        void SetDifficultyLevel(const Type& type);

        Type GetType() const;
        Values GetValues() const;

    private:
        ConfigMap _config = {
            {Type::Easy, {SCREEN_WIDTH * .7f, 2, 1}},
            {Type::EasyMedium, {SCREEN_WIDTH * .8f, 4, 2}},
            {Type::Medium, {SCREEN_WIDTH * .9f, 6, 3}},
            {Type::MediumHard, {SCREEN_WIDTH * 1.2f, 8, 5}},
            {Type::Hard, {SCREEN_WIDTH * 1.4f, 10, 8}},
        };
        Type _type = Type::Medium;
        Values _value = _config.at(_type);
    };
}
