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

        _game.Init(_game);
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
                    const auto& gameState = _game.GetState();

                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        switch (gameState)
                        {
                        case Game::State::MainMenu:
                            _window.close();
                            break;
                        case Game::State::Playing:
                            ResetPauseMenu(_game.GUI.pauseMenu);
                            _game.PushState(Game::State::Pause);
                            break;
                        case Game::State::Pause:
                            _game.PopState();
                            _game.snake.awaitingMoveInput = true;
                            break;
                        default:
                            _game.PopState();
                            break;
                        }
                        break;

                    case sf::Keyboard::Backspace:
                        if (gameState != Game::State::AskNickname)
                        {
                            _game.PopState();
                        }

                        break;

                    case sf::Keyboard::P:
                        switch (gameState)
                        {
                        case Game::State::Playing:
                            ResetPauseMenu(_game.GUI.pauseMenu);
                            _game.PushState(Game::State::Pause);
                            break;
                        case Game::State::Pause:
                            _game.PopState();
                            _game.snake.awaitingMoveInput = true;
                            break;
                        }
                        break;
                    }
                }


                const auto& gameState = _game.GetState();
                switch (gameState)
                {
                case Game::State::Playing:
                    break;
                case Game::State::GameOver:
                    GameOverMenuKeyboardHandler(event, _game);
                    break;
                case Game::State::AskNickname:
                    AskNicknameMenuKeyboardHandler(event, _game);
                    break;
                case Game::State::Pause:
                    PauseMenuKeyboardHandler(event, _game);
                    break;
                case Game::State::MainMenu:
                    _game.GUI.mainMenu.KeyboardHandler(_window, event, _game);
                    break;
                case Game::State::DifficultyLevel:
                    DifficultyLevelMenuKeyboardHandler(event, _game);
                    break;
                case Game::State::Settings:
                    SettingsMenuKeyboardHandler(event, _game);
                case Game::State::Leaderboard:
                    break;
                }
            }

            _game.Update(deltaTime);

            _window.clear();

            _window.setView(_defaultView);
            _game.Draw(_window, _HUDView);

            _window.display();
        }
    }
}
