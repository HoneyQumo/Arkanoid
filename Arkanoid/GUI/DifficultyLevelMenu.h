#pragma once
#include "SFML/Graphics.hpp"
#include "../DifficultyLevel.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class DifficultyLevelMenu
    {
    public:
        void Reset();
        void Init(const Game& game);
        void Draw(sf::RenderWindow& window) const;
        void KeyboardHandler(const sf::Event& event, Game& game);

    private:
        sf::Text _heading;

        std::map<DifficultyLevel::Type, MenuOption> _options = {
            {DifficultyLevel::Type::Easy, {L"Простой", {}}},
            {DifficultyLevel::Type::EasyMedium, {L"Тяжелее простого", {}}},
            {DifficultyLevel::Type::Medium, {L"Средний", {}}},
            {DifficultyLevel::Type::MediumHard, {L"Легче тяжелого", {}}},
            {DifficultyLevel::Type::Hard, {L"Тяжелый", {}}},
        };

        DifficultyLevel::Type _selectedOptionKey = DifficultyLevel::Type::Easy;
    };
}
