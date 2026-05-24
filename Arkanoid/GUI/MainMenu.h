#pragma once

namespace ArkanoidGame
{
    class MainMenu
    {
    public:
        void Reset();

        void Init(const Game& game);

        void Draw(sf::RenderWindow& window) const;

        void KeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game);

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

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::StartGame, {L"Начать игру", {}}},
            {OptionKey::DifficultyLevel, {L"Уровень сложности", {}}},
            {OptionKey::Leaderboard, {L"Таблица рекордов", {}}},
            {OptionKey::Settings, {L"Настройки", {}}},
            {OptionKey::Exit, {L"Выход", {}}},
        };
        OptionKey _selectedOptionKey = OptionKey::StartGame;

        void OptionSelectHandler(sf::RenderWindow& window) const;
    };
}
