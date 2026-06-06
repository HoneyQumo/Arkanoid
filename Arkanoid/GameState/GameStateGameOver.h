#pragma once
#include "GameStateData.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class GameStateGameOver : public GameStateData
    {
    public:
        void Init() override;
        void WindowEventHandler(const sf::Event& event) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        
        
    private:
        enum class OptionKey
        {
            StartGame = 0,
            ExitToMainMenu
        };

        sf::Text _heading;
        sf::Text _scoreTitle;

        sf::Text _leaderboardTitle;
        std::vector<sf::Text> _leaderboard;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::StartGame, {L"Начать игру", {}}},
            {OptionKey::ExitToMainMenu, {L"В главное меню", {}}},
        };

        OptionKey _selectedOptionKey = OptionKey::StartGame;

        void OptionSelectHandler(Game& game) const;
    };
}
