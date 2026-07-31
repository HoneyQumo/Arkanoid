#include <fstream>
#include <algorithm>
#include <string>
#include "SFML/System/String.hpp"
#include "Data/Leaderboard.h"
#include "Core/Game.h"
#include "Shared/Menu.h"

namespace ArkanoidGame
{
    void Leaderboard::Add(unsigned score, const sf::String& nickname)
    {
        const auto playerName = nickname.isEmpty() ? L"XYZ" : nickname.toWideString();

        _array.push_back({playerName, score});

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

    unsigned Leaderboard::GetBestScore() const
    {
        const auto sorted = GetSorted();
        return sorted.empty() ? 0u : sorted.front().score;
    }

    bool Leaderboard::SerializeAndSaveGame() const
    {
        std::ofstream file(LEADERBOARD_FILE_PATH);

        if (!file.is_open())
        {
            return false;
        }

        for (auto item : _array)
        {
            std::replace(item.playerName.begin(), item.playerName.end(), L' ', L'_');

            const auto utf8Name = sf::String(item.playerName).toUtf8();

            file << std::string(utf8Name.begin(), utf8Name.end()) << " " << item.score << "\n";
        }

        return file.good();
    }

    bool Leaderboard::DeserializeAndLoad()
    {
        std::ifstream file(LEADERBOARD_FILE_PATH);

        if (!file.is_open())
        {
            return false;
        }

        _array.clear();

        std::string utf8Name;
        unsigned score = 0;

        while (file >> utf8Name >> score)
        {
            auto playerName = sf::String::fromUtf8(utf8Name.begin(), utf8Name.end()).toWideString();
            std::replace(playerName.begin(), playerName.end(), L'_', L' ');

            _array.push_back({playerName, score});
        }

        return true;
    }

    bool Leaderboard::Clear()
    {
        _array.clear();

        const std::ofstream file(LEADERBOARD_FILE_PATH, std::ios::out | std::ios::trunc);

        return file.is_open();
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
