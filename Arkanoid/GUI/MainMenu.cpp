#include "../Application.h"

namespace ArkanoidGame
{
    void MainMenu::Reset()
    {
        SetOptionKey(_options, _selectedOptionKey, OptionKey::StartGame);
    }


    void MainMenu::Init(const Game& game)
    {
        Reset();

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

    void MainMenu::Draw(sf::RenderWindow& window) const
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
        Game& game = Application::Instance().GetGame();

        switch (_selectedOptionKey)
        {
        case OptionKey::StartGame:
            game.SwitchState(Game::State::Playing);
            break;
        case OptionKey::DifficultyLevel:
            game.PushState(Game::State::DifficultyLevel);
            break;
        case OptionKey::Leaderboard:
            game.gui.leaderboardMenu.UpdateLeaderboard(Application::Instance().GetGame());
            game.PushState(Game::State::Leaderboard);
            break;
        case OptionKey::Settings:
            game.PushState(Game::State::Settings);
            break;
        case OptionKey::Exit:
            window.close();
            break;
        }
    }
}
