#include "GameStateGameOver.h"
#include "Core/Application.h"
#include "Data/Level.h"

namespace ArkanoidGame
{
    void GameStateGameOver::Init(Game& game)
    {
        const bool hasNextLevel = game.GetWin()
            && (game.GetLevelIndex() + 1 < GetLevelCount(game.difficulty.GetType()));

        if (!hasNextLevel)
        {
            _options.erase(OptionKey::NextLevel);
        }

        _selectedOptionKey = hasNextLevel ? OptionKey::NextLevel : OptionKey::StartGame;

        const Level& level = GetLevel(game.difficulty.GetType(), game.GetLevelIndex());
        const auto text = game.GetWin()
                              ? L"\"" + level.name + L"\" " + L"пройден"
                              : L"..::Количество очков::..";
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

        InitHintText(_hint, L"[Up] [Down] Select    [Enter] Confirm    [Backspace] Return", game.assets.font);
    }

    void GameStateGameOver::WindowEventHandler(const sf::Event& event)
    {
        Game& game = Application::Instance().GetGame();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                {
                    game.assets.menuSelect.play();
                    OptionSelectHandler(game);
                    break;
                }
            case sf::Keyboard::Up:
                {
                    game.assets.menuToggle.play();
                    MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Up);

                    break;
                }
            case sf::Keyboard::Down:
                {
                    game.assets.menuToggle.play();
                    MenuToggleOption(_options, _selectedOptionKey, DirectionVertical::Down);

                    break;
                }
            case sf::Keyboard::Escape:
            case sf::Keyboard::Backspace:
                {
                    game.PopStateOrCloseWindow();
                    break;
                }
            }
        }
    }

    void GameStateGameOver::Update(float deltaTime)
    {
        Game& game = Application::Instance().GetGame();

        _scoreTitle.setString(std::to_string(game.GetScore()));

        if (_needsLeaderboardRefresh)
        {
            _needsLeaderboardRefresh = false;
            _leaderboard = game.leaderboard.GetGUI(game, 5);
        }

        if (_recordChecked) return;
        _recordChecked = true;

        if (game.GetScore() > 0 && game.GetScore() > game.leaderboard.GetBestScore())
        {
            _needsLeaderboardRefresh = true;
            game.PushState(GameState::Type::AskNickname);
        }
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

        window.draw(_hint);
    }

    void GameStateGameOver::OptionSelectHandler(Game& game) const
    {
        switch (_selectedOptionKey)
        {
        case OptionKey::NextLevel:
            {
                game.SetWin(false);
                game.SetLevelIndex(game.GetLevelIndex() + 1);
                game.SwitchState(GameState::Type::Playing);
                break;
            }
        case OptionKey::StartGame:
            {
                game.Reset(game);
                game.SwitchState(GameState::Type::Playing);
                break;
            }
        case OptionKey::ExitToMainMenu:
            {
                game.Reset(game);
                break;
            }
        }
    }
}
