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

                _game.WindowEventHandler(event);
            }

            _game.Update(deltaTime);

            _window.clear();
            _game.Draw(_window);
            _window.display();
        }
    }
}
