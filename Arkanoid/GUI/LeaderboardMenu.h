#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    class Game;

    class LeaderboardMenu
    {
    public:
        void UpdateLeaderboard(const Game& game);
        void Init(const Game& game);
        void Draw(sf::RenderWindow& window) const;

        std::vector<sf::Text>& GetLeaderboard();

    private:
        sf::Text _heading;
        std::vector<sf::Text> _leaderboard;
    };
}
