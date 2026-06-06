#include <fstream>
#include <algorithm>
#include "Leaderboard.h"
#include "Game.h"

namespace ArkanoidGame
{
    void Leaderboard::Add(Game& game)
    {
        const auto& nicknameInput = game.gui.askNicknameMenu.GetNicknameInput();
        const auto playerName = nicknameInput.isEmpty() ? L"XYZ" : nicknameInput.toWideString();

        _array.push_back({playerName, game.score});

        std::stable_sort(_array.begin(), _array.end(), [](const Item& item1, const Item& item2)
        {
            return item1.score > item2.score;
        });

        if (_array.size() > 10)
        {
            _array.resize(10);
        }
    }

    std::vector<Leaderboard::Item> Leaderboard::GetSorted() const
    {
        auto leaderboard = _array;

        std::stable_sort(leaderboard.begin(), leaderboard.end(), [](const Item& item1, const Item& item2)
        {
            return item1.score > item2.score;
        });

        return leaderboard;
    }

    bool Leaderboard::SerializeAndSaveGame() const
    {
        std::wofstream file(LEADERBOARD_FILE_PATH);

        if (file.is_open())
        {
            for (auto item : _array)
            {
                std::replace(item.playerName.begin(), item.playerName.end(), L' ', L'_');

                file << item.playerName << L" " << item.score << "\n";
            }

            file.close();
            return true;
        }

        return false;
    }

    bool Leaderboard::DeserializeAndLoad()
    {
        std::wifstream file(LEADERBOARD_FILE_PATH);

        if (file.is_open())
        {
            _array.clear();
            Item tmpItem;

            while (file >> tmpItem.playerName >> tmpItem.score)
            {
                std::replace(tmpItem.playerName.begin(), tmpItem.playerName.end(), L'_', L' ');
                _array.push_back(tmpItem);
            }

            file.close();
            return true;
        }

        return false;
    }

    bool Leaderboard::Clear(LeaderboardMenu& leaderboardMenu)
    {
        _array.clear();
        leaderboardMenu.GetLeaderboard().clear();

        std::wofstream file(LEADERBOARD_FILE_PATH, std::ios::out | std::ios::trunc);

        if (file.is_open())
        {
            file.close();
            return true;
        }

        return false;
    }

    std::vector<sf::Text> Leaderboard::GetGUI(Game& game, const size_t size) const
    {
        std::vector<sf::Text> tmpData;
        const auto leaderboard = GetSorted();

        const auto minSize = std::min(size, leaderboard.size());
        
        for (unsigned i = 0; i < minSize; ++i)
        {
            const auto& item = leaderboard[i];

            sf::Text tmpItem;
            const auto text = std::to_wstring(i + 1) + L". " + item.playerName + L" (" + std::to_wstring(item.score) + L")";
            InitText(tmpItem, text, game.assets.font, TEXT_MENU_ITEM, sf::Color::White, {0.f, 0.5f});
            tmpItem.setPosition(SCREEN_WIDTH / 2.f - 100.f, (SCREEN_HEIGHT / 2.f - 160.f) + (i * 30.f));

            tmpData.push_back(tmpItem);
        }
        
        return tmpData;
    }
}
