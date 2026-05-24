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
        _game.Init(_game);
    }

    // Application::~Application()
    // {
    // ShutdownGame();
    // }

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
                            _game.GUI.pauseMenu.Reset();
                            _game.PushState(Game::State::Pause);
                            break;
                        case Game::State::Pause:
                            _game.PopState();
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
                            _game.GUI.pauseMenu.Reset();
                            _game.PushState(Game::State::Pause);
                            break;
                        case Game::State::Pause:
                            _game.PopState();
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
                    _game.GUI.askNicknameMenu.KeyboardHandler(event, _game);
                    break;
                case Game::State::Pause:
                    _game.GUI.pauseMenu.KeyboardHandler(event, _game);
                    break;
                case Game::State::MainMenu:
                    _game.GUI.mainMenu.KeyboardHandler(_window, event, _game);
                    break;
                case Game::State::DifficultyLevel:
                    _game.GUI.difficultyLevelMenu.KeyboardHandler(event, _game);
                    break;
                case Game::State::Settings:
                    SettingsMenuKeyboardHandler(event, _game);
                case Game::State::Leaderboard:
                    break;
                }
            }

            _game.Update(deltaTime);

            _window.clear();
            _game.Draw(_window);
            _window.display();
        }
    }
}
