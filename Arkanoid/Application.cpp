#include "Application.h"

namespace ArkanoidGame
{
    Application& Application::Instance()
    {
        static Application instance;
        return instance;
    }

    Application::Application()
        : _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_NAME)
    {
        sf::View defaultView(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
        sf::View HUDView(sf::FloatRect(0, 0, SCREEN_WIDTH, HUD_BACKGROUND_HEIGHT));

        defaultView.setViewport(sf::FloatRect(0.f, HUD_VIEW_PERCENT, 1.f, DEFAULT_VIEW_PERCENT));
        HUDView.setViewport(sf::FloatRect(0.f, 0.0f, 1.f, HUD_VIEW_PERCENT));

        InitGame(_game);
    }

    Application::~Application()
    {
        // ShutdownGame();
    }

    void Application::Run()
    {
        sf::Clock gameClock;
        float lastTime = gameClock.getElapsedTime().asSeconds();

        while (_window.isOpen())
        {
            float currentTime = gameClock.getElapsedTime().asSeconds();
            float deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            sf::Event event;
            while (_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    _window.close();
                    break;
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    const auto& gameState = GetCurrentGameState(_game);

                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        switch (gameState)
                        {
                        case GameState::MainMenu:
                            _window.close();
                            break;
                        case GameState::Playing:
                            ResetPauseMenu(_game.GUI.pauseMenu);
                            PushGameState(_game, GameState::Pause);
                            break;
                        case GameState::Pause:
                            PopGameState(_game);
                            _game.snake.awaitingMoveInput = true;
                            break;
                        default:
                            PopGameState(_game);
                            break;
                        }
                        break;

                    case sf::Keyboard::Backspace:
                        if (gameState != GameState::AskNickname)
                        {
                            PopGameState(_game);
                        }

                        break;

                    case sf::Keyboard::P:
                        switch (gameState)
                        {
                        case GameState::Playing:
                            ResetPauseMenu(_game.GUI.pauseMenu);
                            PushGameState(_game, GameState::Pause);
                            break;
                        case GameState::Pause:
                            PopGameState(_game);
                            _game.snake.awaitingMoveInput = true;
                            break;
                        }
                        break;
                    }
                }


                const auto& gameState = GetCurrentGameState(_game);
                switch (gameState)
                {
                case GameState::Playing:
                    break;
                case GameState::GameOver:
                    GameOverMenuKeyboardHandler(event, _game);
                    break;
                case GameState::AskNickname:
                    AskNicknameMenuKeyboardHandler(event, _game);
                    break;
                case GameState::Pause:
                    PauseMenuKeyboardHandler(event, _game);
                    break;
                case GameState::MainMenu:
                    MainMenuKeyboardHandler(_window, event, _game);
                    break;
                case GameState::DifficultyLevel:
                    DifficultyLevelMenuKeyboardHandler(event, _game);
                    break;
                case GameState::Settings:
                    SettingsMenuKeyboardHandler(event, _game);
                case GameState::Leaderboard:
                    break;
                }
            }

            UpdateGame(_game, deltaTime);

            _window.clear();

            _window.setView(_defaultView);
            DrawGame(_game, _window, _HUDView);

            _window.display();
        }
    }
}
