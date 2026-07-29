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

        InitHintText(_hint, L"[Backspace] Return", game.assets.font);
    }

    void GameStateLeaderboard::Update(float deltaTime)
    {
    }

    void GameStateLeaderboard::WindowEventHandler(const sf::Event& event)
    {
        Game& game = Application::Instance().GetGame();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            case sf::Keyboard::Backspace:
                {
                    game.PopStateOrCloseWindow();
                    break;
                }
            }
        }
    }

    void GameStateLeaderboard::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);

        for (auto& item : _leaderboard)
        {
            window.draw(item);
        }

        window.draw(_hint);
    }
}
