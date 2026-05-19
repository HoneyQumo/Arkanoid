#pragma once
#include "SFML/Graphics.hpp"
#include "../DifficultyLevel.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    struct DifficultyLevelMenu
    {
        sf::Text heading;

        std::map<DifficultyLevel::Type, MenuOption> options = {
            {DifficultyLevel::Type::Easy, {L"Простой", {}}},
            {DifficultyLevel::Type::EasyMedium, {L"Тяжелее простого", {}}},
            {DifficultyLevel::Type::Medium, {L"Средний", {}}},
            {DifficultyLevel::Type::MediumHard, {L"Легче тяжелого", {}}},
            {DifficultyLevel::Type::Hard, {L"Тяжелый", {}}},
        };

        DifficultyLevel::Type selectedOptionKey = DifficultyLevel::Type::Easy;
    };

    void ResetDifficultyLevelMenu(DifficultyLevelMenu& difficultyLevelMenu);
    class Game;
    void InitDifficultyLevelMenu(Game& game);
    void DrawDifficultyLevelMenu(sf::RenderWindow& window, const DifficultyLevelMenu& difficultyLevelMenu);

    void DifficultyLevelMenuKeyboardHandler(const sf::Event& event, Game& game);
}
