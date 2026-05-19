#pragma once
#include <stack>
#include "DifficultyLevel.h"
#include "Leaderboard.h"
#include "Platform.h"
#include "GUI/GUI.h"
#include "Shared/Assets.h"
#include "Shared/Constants.h"

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
        unsigned score = 0;
        bool isWin = false;

        Platform platform;

        DifficultyLevel difficulty;
        Settings settings;
        Leaderboard leaderboard;

        void ResetState();
        void PushState(const State& state);
        void PopState();
        void SwitchState(const State& state);
        State GetState();

        void Reset(Game& game);
        void Init(Game& game);
        void Update(const float& deltaTime);
        void Draw(sf::RenderWindow& window);

        // void ShutdownGame();

    private:
        std::stack<State> _gameStateStack;
    };
}
