#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics/Text.hpp"

namespace ArkanoidGame
{
    class Game;
    class LeaderboardMenu;

    class Leaderboard
    {
    public:
        struct Item
        {
            std::wstring playerName;
            unsigned score;
        };

        void Add(Game& game);
        std::vector<Item> GetSorted() const;

        bool SerializeAndSaveGame() const;
        bool DeserializeAndLoad();

        bool Clear(LeaderboardMenu& leaderboardMenu);
        
        std::vector<sf::Text> GetGUI(Game& game, const size_t size = 5) const;

    private:
        std::vector<Item> _array;
    };
}
