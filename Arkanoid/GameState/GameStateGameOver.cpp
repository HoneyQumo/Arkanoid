#include "GameStateGameOver.h"
#include "../Application.h"

namespace ArkanoidGame
{
    void GameStateGameOver::Init()
    {
        Game& game = Application::Instance().GetGame();
        
        const auto text = game.GetWin() ? L"..::Победа::.." : L"..::Количество очков::..";
        InitText(_heading, std::wstring(text), game.assets.font);
        _heading.setStyle(sf::Text::Bold);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        InitText(_scoreTitle, std::to_string(game.GetScore()), game.assets.font, TEXT_HEADING_2);
        _scoreTitle.setStyle(sf::Text::Bold);
        _scoreTitle.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT + 60.f);

        InitText(_leaderboardTitle, std::wstring(L"Рекорды"), game.assets.font, TEXT_HEADING_3);
        _leaderboardTitle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 200.f);
        _leaderboard = game.leaderboard.GetGUI(game, 5);

        int index = 0;
        for (auto& option : _options)
        {
            const auto color = _selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - OFFSET_TOP_WINDOW_10_PERCENT - (_options.size() - index) * 30.f);
            index++;
        }
    }

    void GameStateGameOver::WindowEventHandler(const sf::Event& event)
    {
        Game& game = Application::Instance().GetGame();
        
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.assets.menuSelect.play();
                OptionSelectHandler(game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Down);
            }
        }
    }

    void GameStateGameOver::Update(float deltaTime)
    {
        _scoreTitle.setString(Application::Instance().GetGame().GetScore());
    }

    void GameStateGameOver::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);
        window.draw(_scoreTitle);
        window.draw(_leaderboardTitle);

        for (const auto& item : _leaderboard)
        {
            window.draw(item);
        }

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void GameStateGameOver::OptionSelectHandler(Game& game) const
    {
        switch (_selectedOptionKey)
        {
        case OptionKey::StartGame:
            game.Reset(game);
            game.SwitchState(GameState::Type::Playing);
            break;
        case OptionKey::ExitToMainMenu:
            game.Reset(game);
            break;
        }
    }
}
