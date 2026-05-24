#include "../Game.h"

namespace ArkanoidGame
{
    void LeaderboardMenu::UpdateLeaderboard(const Game& game)
    {
        _leaderboard.clear();
        const auto& leaderboard = game.leaderboard.GetSorted();

        for (unsigned i = 0; i < leaderboard.size(); ++i)
        {
            const auto& item = leaderboard[i];

            sf::Text tmpItem;
            const auto text = std::to_wstring(i + 1) + L". " + item.playerName + L" (" + std::to_wstring(item.score) + L")";
            InitText(tmpItem, text, game.assets.font, TEXT_HEADING_3, sf::Color::White, {0.f, 0.5f});
            tmpItem.setPosition(SCREEN_WIDTH / 2.f - 120.f, (OFFSET_TOP_WINDOW_20_PERCENT) + (i * 40.f));

            _leaderboard.push_back(tmpItem);
        }
    }

    void LeaderboardMenu::Init(const Game& game)
    {
        InitText(_heading, L"..::Таблица рекордов::..", game.assets.font, TEXT_HEADING_1);
        _heading.setStyle(sf::Text::Underlined | sf::Text::Bold);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        UpdateLeaderboard(game);
    }

    void LeaderboardMenu::Draw(sf::RenderWindow& window) const
    {
        window.draw(_heading);

        for (auto& item : _leaderboard)
        {
            window.draw(item);
        }
    }

    std::vector<sf::Text>& LeaderboardMenu::GetLeaderboard()
    {
        return _leaderboard;
    }
}
