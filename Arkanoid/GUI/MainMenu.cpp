#include "../Application.h"
#include "../Game.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    void MainMenu::ResetMainMenu()
    {
        SetOptionKey(_options, _selectedOptionKey, MainMenuOptionKey::StartGame);
    }


    void MainMenu::InitMainMenu(const Game& game)
    {
        ResetMainMenu();

        InitText(_heading, "..::MAIN MENU::..", game.assets.font);
        _heading.setStyle(sf::Text::Underlined);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : _options)
        {
            const auto color = _selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            index++;
        }
    }

    void MainMenu::DrawMainMenu(sf::RenderWindow& window) const
    {
        window.draw(_heading);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void MainMenu::KeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // Game& game = Application::Instance().GetGame();

            if (event.key.code == sf::Keyboard::Enter)
            {
                OptionSelectHandler(window);
                game.assets.menuSelect.play();
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Up);
                game.assets.menuToggle.play();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Down);
                game.assets.menuToggle.play();
            }
        }
    }

    void MainMenu::OptionSelectHandler(sf::RenderWindow& window) const
    {
        switch (_selectedOptionKey)
        {
        case MainMenuOptionKey::StartGame:
            SwitchGameState(Application::Instance().GetGame(), GameState::Playing);
            break;
        case MainMenuOptionKey::DifficultyLevel:
            PushGameState(Application::Instance().GetGame(), GameState::DifficultyLevel);
            break;
        case MainMenuOptionKey::Leaderboard:
            UpdateLeaderboardInLeaderboardMenu(Application::Instance().GetGame());
            PushGameState(Application::Instance().GetGame(), GameState::Leaderboard);
            break;
        case MainMenuOptionKey::Settings:
            PushGameState(Application::Instance().GetGame(), GameState::Settings);
            break;
        case MainMenuOptionKey::Exit:
            window.close();
            break;
        }
    }
}
