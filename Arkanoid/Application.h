#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
    class Application
    {
    public:
        Application(const Application& app) = delete;
        Application& operator=(const Application&) = delete;

        static Application& Instance();

        void Run();

        Game& GetGame() { return _game; }
        sf::RenderWindow& GetWindow() { return _window; }

    private:
        Application();
        // ~Application();

        Game _game;
        sf::RenderWindow _window;
    };
}
