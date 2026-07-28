#include "Game.h"
#include "Application.h"

namespace ArkanoidGame
{
    void Game::ResetState()
    {
        SwitchState(GameState::Type::MainMenu);
    }

    void Game::PushState(const GameState::Type& state)
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

    void Game::SwitchState(const GameState::Type& state)
    {
        while (!_gameStateStack.empty())
        {
            _gameStateStack.pop();
        }

        PushState(state);
    }

    GameState::Type Game::GetState()
    {
        if (!_gameStateStack.empty())
        {
            return _gameStateStack.top().GetType();
        }

        return GameState::Type::MainMenu;
    }

    void Game::Reset(Game& game)
    {
        ResetState();

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
        _gameStateStack.top().Update(deltaTime);
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        _gameStateStack.top().Draw(window);
    }

    void Game::WindowEventHandler(sf::Event& event)
    {
        _gameStateStack.top().WindowEventHandler(event);
    }

    // void Game::ShutdownGame()
    // {
    // }
}
