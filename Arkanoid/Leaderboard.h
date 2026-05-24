#pragma once
#include <string>
#include <vector>

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

    private:
        std::vector<Item> _array;
    };
}
