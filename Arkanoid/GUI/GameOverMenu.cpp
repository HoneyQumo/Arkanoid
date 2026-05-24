#include "GameOverMenu.h"
#include "../Game.h"


namespace ArkanoidGame
{
    void GameOverMenu::Reset()
    {
        SetOptionKey(_options, _selectedOptionKey, OptionKey::StartGame);
    }

    void GameOverMenu::UpdateLeaderboard(const Game& game)
    {
        _leaderboard.clear();
        const auto& leaderboard = GetSortedLeaderboard(game.leaderboard.array);

        for (unsigned i = 0; i < std::min(5, static_cast<const int&>(leaderboard.size())); ++i)
        {
            const auto& item = leaderboard[i];

            sf::Text tmpItem;
            const auto text = std::to_wstring(i + 1) + L". " + item.playerName + L" (" + std::to_wstring(item.score) + L")";
            InitText(tmpItem, text, game.assets.font, TEXT_MENU_ITEM, sf::Color::White, {0.f, 0.5f});
            tmpItem.setPosition(SCREEN_WIDTH / 2.f - 100.f, (SCREEN_HEIGHT / 2.f - 160.f) + (i * 30.f));

            _leaderboard.push_back(tmpItem);
        }
    }

    void GameOverMenu::Init(Game& game)
    {
        Reset();

        const auto text = game.isWin ? L"..::Победа::.." : L"..::Количество очков::..";
        InitText(_heading, std::wstring(text), game.assets.font);
        _heading.setStyle(sf::Text::Bold);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        InitText(_scoreTitle, std::to_string(game.score), game.assets.font, TEXT_HEADING_2);
        _scoreTitle.setStyle(sf::Text::Bold);
        _scoreTitle.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT + 60.f);

        InitText(_recordsTitle, std::wstring(L"Рекорды"), game.assets.font, TEXT_HEADING_3);
        _recordsTitle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 200.f);

        UpdateLeaderboard(game);

        int index = 0;
        for (auto& option : _options)
        {
            const auto color = _selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - OFFSET_TOP_WINDOW_10_PERCENT - (_options.size() - index) * 30.f);
            index++;
        }
    }

    void GameOverMenu::Update(const Game& game)
    {
        _scoreTitle.setString(std::to_string(game.score));
    }

    void GameOverMenu::Draw(sf::RenderWindow& window) const
    {
        window.draw(_heading);
        window.draw(_scoreTitle);
        window.draw(_recordsTitle);

        for (const auto& item : _leaderboard)
        {
            window.draw(item);
        }

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void GameOverMenu::OptionSelectHandler(Game& game) const
    {
        switch (_selectedOptionKey)
        {
        case OptionKey::StartGame:
            game.Reset(game);
            game.SwitchState(Game::State::Playing);
            break;
        case OptionKey::ExitToMainMenu:
            game.Reset(game);
            break;
        }
    }

    void GameOverMenu::KeyboardHandler(const sf::Event& event, Game& game)
    {
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
}
