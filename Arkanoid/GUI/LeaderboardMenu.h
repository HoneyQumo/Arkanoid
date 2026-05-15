#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    struct LeaderboardMenu
    {
        sf::Text heading;
        std::vector<sf::Text> leaderboard;
    };

    class Game;
    void UpdateLeaderboardInLeaderboardMenu(Game& game);
    void InitLeaderboardMenu(Game& game);
    void DrawLeaderboardMenu(sf::RenderWindow& window, const LeaderboardMenu& leaderboardMenu);
}
