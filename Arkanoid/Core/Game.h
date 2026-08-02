#pragma once
#include <stack>

#include "Objects/Ball.h"
#include "Data/DifficultyLevel.h"
#include "Data/Leaderboard.h"
#include "Objects/Platform.h"
#include "Core/Settings.h"
#include "Core/Assets.h"
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

        void StartGame();
        void StartNextLevel();
        void RestartGame();
        void PauseGame();
        void ResumeGame();
        void WinGame();
        void LoseGame();
        void ExitToMenu();
        void GoBack();
        void ShowDifficultySelect();
        void ShowLeaderboard();
        void ShowSettings();
        void AskForNickname();

        void Init();
        void UpdateGame(float deltaTime, sf::RenderWindow& window);

        void SetScore(unsigned value) { _score = value; }
        unsigned GetScore() const { return _score; }

        void SetWin(bool value) { _isWin = value; }
        bool GetWin() const { return _isWin; }

        void SetLevelIndex(size_t value) { _levelIndex = value; }
        size_t GetLevelIndex() const { return _levelIndex; }

        void SetLives(unsigned value) { _lives = value; }
        unsigned GetLives() const { return _lives; }

    private:
        void Reset();

        void PushState(const GameState::Type& state);
        void PopState();
        void SwitchState(const GameState::Type& state);
        GameState::Type GetState() const;

        void HandleWindowEvents(sf::RenderWindow& window);
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        void WindowEventHandler(sf::Event& event);

        static void ReleaseMouse();

        std::stack<GameState> _gameStateStack;
        size_t _levelIndex = 0;
        unsigned _score = 0;
        unsigned _lives = PLAYER_INITIAL_LIVES;
        bool _isWin = false;
    };
}
