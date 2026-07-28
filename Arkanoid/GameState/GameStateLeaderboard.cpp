#include "GameStateLeaderboard.h"
#include "../Application.h"
#include "../Shared/Shared.h"


namespace ArkanoidGame
{
    void GameStateLeaderboard::Init(Game& game)
    {
        InitText(_heading, L"..::Таблица рекордов::..", game.assets.font, TEXT_HEADING_1);
        _heading.setStyle(sf::Text::Underlined | sf::Text::Bold);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        _leaderboard = game.leaderboard.GetGUI(game, 10);
    }

    void GameStateLeaderboard::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);

        for (auto& item : _leaderboard)
        {
            window.draw(item);
        }
    }
}
