#pragma once
#include <stack>
#include "Apple.h"
#include "Field.h"
#include "DifficultyLevel.h"
#include "Leaderboard.h"
#include "GUI/GUI.h"
#include "Shared/Assets.h"
#include "Shared/Constants.h"
#include "Snake/Snake.h"

namespace ArkanoidGame
{
    class Game
    {
    public:
        enum class State
        {
            Playing = 0,
            GameOver,
            Pause,
            MainMenu,
            DifficultyLevel,
            Settings,
            Leaderboard,
            AskNickname
        };

        Assets assets;

        GUI GUI;

        Field field;
        Snake snake;
        std::vector<Apple> apples;

        unsigned score = 0;
        bool isWin = false;

        DifficultyLevel difficulty;
        Settings settings;
        Leaderboard leaderboard;

        void ResetState();
        void PushState(const State& state);
        void PopState();
        void SwitchState(const State& state);
        State GetState();

        void ResetGame(Game& game);
        void InitGame(Game& game);
        void UpdateGame(const float& deltaTime);
        void DrawGame(sf::RenderWindow& window, const sf::View& HUDView);

        // void ShutdownGame();

    private:
        std::stack<State> _gameStateStack;
    };
}
