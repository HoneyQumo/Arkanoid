#include "GameStateMainMenu.h"

namespace ArkanoidGame
{
    void GameStateMainMenu::Init()
    {
        Game& game = Application::Instance().GetGame();

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

    void GameStateMainMenu::WindowEventHandler(const sf::Event& event)
    {
        Game& game = Application::Instance().GetGame();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                {
                    OptionSelectHandler();
                    game.assets.menuSelect.play();
                    break;
                }
            case sf::Keyboard::Up:
                {
                    MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Up);
                    game.assets.menuToggle.play();
                    break;
                }
            case sf::Keyboard::Down:
                {
                    MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Down);
                    game.assets.menuToggle.play();
                    break;
                }
            case sf::Keyboard::Escape:
                {
                    Application::Instance().GetWindow().close();
                    break;
                }
            }
        }
    }

    void GameStateMainMenu::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void GameStateMainMenu::OptionSelectHandler() const
    {
        Game& game = Application::Instance().GetGame();

        switch (_selectedOptionKey)
        {
        case OptionKey::StartGame:
            game.SwitchState(GameState::Type::Playing);
            break;
        case OptionKey::DifficultyLevel:
            game.PushState(GameState::Type::DifficultyLevel);
            break;
        case OptionKey::Leaderboard:
            game.PushState(GameState::Type::Leaderboard);
            break;
        case OptionKey::Settings:
            game.PushState(GameState::Type::Settings);
            break;
        case OptionKey::Exit:
            Application::Instance().GetWindow().close();
            break;
        }
    }
}
