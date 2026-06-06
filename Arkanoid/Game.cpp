#include "Game.h"
#include "Application.h"

namespace ArkanoidGame
{
    void Game::ResetState()
    {
        SwitchState(State::MainMenu);
    }

    void Game::PushState(const State& state)
    {
        _gameStateStack.push(state);
    }

    void Game::PopState()
    {
        if (_gameStateStack.size() != 1)
        {
            _gameStateStack.pop();
        }
    }

    void Game::SwitchState(const State& state)
    {
        while (!_gameStateStack.empty())
        {
            _gameStateStack.pop();
        }

        PushState(state);
    }

    Game::State Game::GetState()
    {
        if (!_gameStateStack.empty())
        {
            return _gameStateStack.top();
        }

        return State::MainMenu;
    }

    void Game::Reset(Game& game)
    {
        ResetState();

        /* gui */
        gui.Init(game);

        /* Sounds */
        assets.music.setPlayingOffset(sf::seconds(0.f));
        assets.music.setLoop(true);

        if (settings.GetState(Settings::Type::Music))
        {
            assets.music.play();
        }
        
        game.SetScore(0);
        game.SetWin(false);
    }

    void Game::Init(Game& game)
    {
        game.assets.Init();
        
        difficulty.SetDifficultyLevel(DifficultyLevel::Type::Medium);

        leaderboard.DeserializeAndLoad();

        Reset(game);
    }


    void Game::Update(float deltaTime)
    {
        const State& gameState = GetState();

        switch (gameState)
        {
        case State::MainMenu:
            break;
        case State::Pause:
        case State::DifficultyLevel:
        case State::Settings:
        case State::Leaderboard:
            break;
        }
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        const State& gameState = GetState();

        switch (gameState)
        {
        case State::MainMenu:
            gui.mainMenu.Draw(window);

            break;

        case State::AskNickname:
            gui.askNicknameMenu.Draw(window);

            break;
        case State::Pause:
            gui.pauseMenu.Draw(window);

            break;
        case State::DifficultyLevel:
            gui.difficultyLevelMenu.Draw(window);

            break;
        case State::Settings:
            gui.settingsMenu.Draw(window);
            break;
        case State::Leaderboard:
            gui.leaderboardMenu.Draw(window);
            break;
        }
    }

    // void Game::ShutdownGame()
    // {
    // }
}
