#pragma once
#include "GameStateData.h"
#include "SFML/Graphics.hpp"


namespace ArkanoidGame
{
    class Game;

    class GameStateLeaderboard : public GameStateData
    {
    public:
        void Init(Game& game) override;
        void Update(float deltaTime) override;
        void WindowEventHandler(const sf::Event& event) override;
        void Draw(sf::RenderWindow& window) override;

        std::vector<sf::Text>& GetLeaderboard() { return _leaderboard; }

    private:
        sf::Text _heading;
        sf::Text _hint;
        std::vector<sf::Text> _leaderboard;
    };
}
