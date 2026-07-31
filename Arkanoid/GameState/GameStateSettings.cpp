#include "GameStateSettings.h"
#include "Core/Game.h"
#include "Shared/Menu.h"

namespace ArkanoidGame
{
    void GameStateSettings::Init(Game& game)
    {
        InitText(_heading, L"..::Настройки::..", game.assets.font);
        _heading.setStyle(sf::Text::Underlined);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : _options)
        {
            const auto color = _selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));

            if (game.settings.GetState(option.first))
            {
                option.second.textNode.setStyle(sf::Text::Underlined);
            }

            index++;
        }

        InitHintText(_hint, L"[Up] [Down] Select    [Enter] Toggle    [Backspace] Return", game.assets.font);
    }

    void GameStateSettings::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }

        window.draw(_hint);
    }

    void GameStateSettings::WindowEventHandler(const sf::Event& event)
    {
        Game& game = Application::Instance().GetGame();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                {
                    game.assets.menuSelect.play();

                    for (auto& option : _options)
                    {
                        if (option.first != Settings::Type::ResetLeaderboard && option.first == _selectedOptionKey)
                        {
                            const auto& style = option.second.textNode.getStyle();
                            option.second.textNode.setStyle(style == sf::Text::Underlined ? sf::Text::Regular : sf::Text::Underlined);
                            break;
                        }
                    }

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

    void GameStateSettings::Update(float deltaTime)
    {
    }

    void GameStateSettings::OptionSelectHandler(Game& game) const
    {
        switch (_selectedOptionKey)
        {
        case Settings::Type::Sound:
            {
                auto& isSoundState = game.settings.GetState(Settings::Type::Sound);
                isSoundState = !isSoundState;

                game.assets.death.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);
                game.assets.menuToggle.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);
                game.assets.menuSelect.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);

                break;
            }
        case Settings::Type::Music:
            {
                auto& isMusicState = game.settings.GetState(Settings::Type::Music);
                isMusicState = !isMusicState;

                if (isMusicState)
                {
                    game.assets.music.setVolume(MUSIC_INITIAL_VOLUME);
                    game.assets.music.play();
                }
                else
                {
                    game.assets.music.setVolume(0.f);
                    game.assets.music.stop();
                }

                break;
            }
        case Settings::Type::ResetLeaderboard:
            game.leaderboard.Clear();
            break;
        }
    }
}
