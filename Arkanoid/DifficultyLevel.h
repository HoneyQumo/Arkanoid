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
        };

        using ConfigMap = std::map<Type, Values>;

        void SetDifficultyLevel(const Type& type);

        Type GetType() const;
        Values GetValues() const;

    private:
        ConfigMap _config = {
            {Type::Easy, {SCREEN_WIDTH * .5f, 2}},
            {Type::EasyMedium, {SCREEN_WIDTH * .6f, 4}},
            {Type::Medium, {SCREEN_WIDTH * .7f, 6}},
            {Type::MediumHard, {SCREEN_WIDTH * .8f, 8}},
            {Type::Hard, {SCREEN_WIDTH * 1.f, 10}},
        };
        Type _type = Type::Medium;
        Values _value = _config.at(_type);
    };
}
