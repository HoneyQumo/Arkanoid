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

        void Add(unsigned score, const sf::String& nickname);
        std::vector<Item> GetSorted() const;
        unsigned GetBestScore() const;

        bool SerializeAndSaveGame() const;
        bool DeserializeAndLoad();

        bool Clear();

        std::vector<sf::Text> GetGUI(Game& game, size_t size = 5) const;

    private:
        std::vector<Item> _array;
    };
}
