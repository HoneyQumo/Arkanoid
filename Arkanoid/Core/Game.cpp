#include "Core/Game.h"

#include <cassert>

#include "Core/Application.h"

namespace ArkanoidGame
{
    void Game::Init()
    {
        assets.Init();

        difficulty.SetDifficultyLevel(DifficultyLevel::Type::Medium);

        leaderboard.DeserializeAndLoad();

        Reset();
    }

    void Game::UpdateGame(const float deltaTime, sf::RenderWindow& window)
    {
        HandleWindowEvents(window);

        if (!window.isOpen()) return;

        Update(deltaTime);

        window.clear();
        Draw(window);
        window.display();
    }

    void Game::StartGame()
    {
        SwitchState(GameState::Type::Playing);
    }

    void Game::StartNextLevel()
    {
        SetWin(false);
        SetLevelIndex(GetLevelIndex() + 1);
        SwitchState(GameState::Type::Playing);
    }

    void Game::RestartGame()
    {
        Reset();
        SwitchState(GameState::Type::Playing);
    }

    void Game::PauseGame()
    {
        ReleaseMouse();
        PushState(GameState::Type::Pause);
    }

    void Game::ResumeGame()
    {
        PopState();
    }

    void Game::WinGame()
    {
        ReleaseMouse();
        SetWin(true);
        PushState(GameState::Type::GameOver);
    }

    void Game::LoseGame()
    {
        ReleaseMouse();
        SetWin(false);
        PushState(GameState::Type::GameOver);
    }

    void Game::ExitToMenu()
    {
        Reset();
    }

    void Game::GoBack()
    {
        if (GetState() == GameState::Type::MainMenu)
        {
            Application::Instance().GetWindow().close();
        }
        else
        {
            PopState();
        }
    }

    void Game::ShowDifficultySelect()
    {
        PushState(GameState::Type::DifficultyLevel);
    }

    void Game::ShowLeaderboard()
    {
        PushState(GameState::Type::Leaderboard);
    }

    void Game::ShowSettings()
    {
        PushState(GameState::Type::Settings);
    }

    void Game::AskForNickname()
    {
        PushState(GameState::Type::AskNickname);
    }

    void Game::Reset()
    {
        SwitchState(GameState::Type::MainMenu);

        /* Sounds */
        assets.music.setPlayingOffset(sf::seconds(0.f));
        assets.music.setLoop(true);

        if (settings.GetState(Settings::Type::Music))
        {
            assets.music.play();
        }

        SetLevelIndex(0);
        SetScore(0);
        SetLives(PLAYER_INITIAL_LIVES);
        SetWin(false);
    }

    void Game::PushState(const GameState::Type& state)
    {
        _gameStateStack.push(GameState(state, *this));
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

    GameState::Type Game::GetState() const
    {
        assert(!_gameStateStack.empty());
        return _gameStateStack.top().GetType();
    }

    void Game::HandleWindowEvents(sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            WindowEventHandler(event);
        }
    }

    void Game::Update(const float deltaTime)
    {
        assert(!_gameStateStack.empty());
        _gameStateStack.top().Update(deltaTime);
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        assert(!_gameStateStack.empty());
        _gameStateStack.top().Draw(window);
    }

    void Game::WindowEventHandler(sf::Event& event)
    {
        assert(!_gameStateStack.empty());
        _gameStateStack.top().WindowEventHandler(event);
    }

    void Game::ReleaseMouse()
    {
        auto& window = Application::Instance().GetWindow();

        window.setMouseCursorVisible(true);
        window.setMouseCursorGrabbed(false);
    }
}
