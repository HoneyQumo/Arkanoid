#pragma once
#include "GameStateData.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class GameStateGameOver : public GameStateData
    {
    public:
        void Init(Game& game) override;
        void WindowEventHandler(const sf::Event& event) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        enum class OptionKey
        {
            NextLevel = 0,
            StartGame,
            ExitToMainMenu
        };

        sf::Text _heading;
        sf::Text _scoreTitle;

        sf::Text _leaderboardTitle;
        std::vector<sf::Text> _leaderboard;

        bool _recordChecked = false;
        bool _needsLeaderboardRefresh = false;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::NextLevel, {L"Следующий уровень", {}}},
            {OptionKey::StartGame, {L"Пройти заново", {}}},
            {OptionKey::ExitToMainMenu, {L"В главное меню", {}}},
        };

        OptionKey _selectedOptionKey = OptionKey::StartGame;

        void OptionSelectHandler(Game& game) const;
    };
}
