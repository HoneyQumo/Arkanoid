#pragma once
#include "GameStateData.h"
#include "Core/Application.h"
#include "Shared/Menu.h"

namespace ArkanoidGame
{
    class GameStateMainMenu : public GameStateData
    {
    public:
        void Init(Game& game) override;
        void WindowEventHandler(const sf::Event& event) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        enum class OptionKey
        {
            StartGame = 0,
            DifficultyLevel,
            Leaderboard,
            Settings,
            Exit
        };

        sf::Text _heading;
        sf::Text _hint;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::StartGame, {L"Начать игру", {}}},
            {OptionKey::DifficultyLevel, {L"Уровень сложности", {}}},
            {OptionKey::Leaderboard, {L"Таблица рекордов", {}}},
            {OptionKey::Settings, {L"Настройки", {}}},
            {OptionKey::Exit, {L"Выход", {}}},
        };
        OptionKey _selectedOptionKey = OptionKey::StartGame;

        void OptionSelectHandler() const;
    };
}
