#pragma once
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "../Shared/Constants.h"
#include "../Shared/Math.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class MainMenu
    {
    public:
        enum class MainMenuOptionKey
        {
            StartGame = 0,
            DifficultyLevel,
            Leaderboard,
            Settings,
            Exit
        };

        void ResetMainMenu();

        void InitMainMenu(const Game& game);

        void DrawMainMenu(sf::RenderWindow& window) const;

        void KeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game);

    private:
        sf::Text _heading;

        std::map<MainMenuOptionKey, MenuOption> _options = {
            {MainMenuOptionKey::StartGame, {L"Начать игру", {}}},
            {MainMenuOptionKey::DifficultyLevel, {L"Уровень сложности", {}}},
            {MainMenuOptionKey::Leaderboard, {L"Таблица рекордов", {}}},
            {MainMenuOptionKey::Settings, {L"Настройки", {}}},
            {MainMenuOptionKey::Exit, {L"Выход", {}}},
        };
        MainMenuOptionKey _selectedOptionKey = MainMenuOptionKey::StartGame;

        void OptionSelectHandler(sf::RenderWindow& window) const;
    };
}
