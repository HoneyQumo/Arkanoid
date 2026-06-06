#include "../Game.h"

namespace ArkanoidGame
{
    void LeaderboardMenu::Init(Game& game)
    {
        InitText(_heading, L"..::Таблица рекордов::..", game.assets.font, TEXT_HEADING_1);
        _heading.setStyle(sf::Text::Underlined | sf::Text::Bold);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        _leaderboard = game.leaderboard.GetGUI(game, 10);
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
