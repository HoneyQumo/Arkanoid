#pragma once
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class GameOverMenu
    {
    public:
        void Reset();

        void UpdateLeaderboard(const Game& game);
        void Init(Game& game);
        void Update(const Game& game);
        void Draw(sf::RenderWindow& window) const;

        void OptionSelectHandler(Game& game) const;
        void KeyboardHandler(const sf::Event& event, Game& game);

    private:
        enum class OptionKey
        {
            StartGame = 0,
            ExitToMainMenu
        };

        sf::Text _heading;
        sf::Text _scoreTitle;

        sf::Text _recordsTitle;
        std::vector<sf::Text> _leaderboard;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::StartGame, {L"Начать игру", {}}},
            {OptionKey::ExitToMainMenu, {L"В главное меню", {}}},
        };

        OptionKey _selectedOptionKey = OptionKey::StartGame;
    };
}
