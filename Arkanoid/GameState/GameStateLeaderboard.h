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
        void Draw(sf::RenderWindow& window) override;

        std::vector<sf::Text>& GetLeaderboard() { return _leaderboard; }

    private:
        sf::Text _heading;
        std::vector<sf::Text> _leaderboard;
    };
}
