#pragma once
#include <stack>

#include "Ball.h"
#include "DifficultyLevel.h"
#include "Leaderboard.h"
#include "Platform.h"
#include "Settings.h"
#include "Shared/Assets.h"
#include "GameState/GameState.h"

namespace ArkanoidGame
{
    class Game
    {
    public:
        Assets assets;

        DifficultyLevel difficulty;
        Settings settings;
        Leaderboard leaderboard;

        void ResetState();
        void PushState(const GameState::Type& state);
        void PopState();
        void SwitchState(const GameState::Type& state);
        GameState::Type GetState();

        void Reset(Game& game);
        void Init(Game& game);
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

        // void ShutdownGame();
        
        void SetScore(unsigned value) { _score = value; }
        unsigned GetScore() const { return _score; }
        
        void SetWin(bool value) { _isWin = value; }
        bool GetWin() const { return _isWin; }

    private:
        std::stack<GameState> _gameStateStack;
        unsigned _score = 0;
        bool _isWin = false;
        
    };
}
