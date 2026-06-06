#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

namespace ArkanoidGame
{
    class GameStateData
    {
    public:
        virtual ~GameStateData() = default;
        
        virtual void Init() = 0;
        virtual void WindowEventHandler(const sf::Event& event) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw(sf::RenderWindow& window) = 0;
    };
}
