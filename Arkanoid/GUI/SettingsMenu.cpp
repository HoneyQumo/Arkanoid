#include "../Game.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    void SettingsMenu::Reset()
    {
        SetOptionKey(_options, _selectedOptionKey, SettingsType::Sound);
    }

    void SettingsMenu::Init(Game& game)
    {
        Reset();

        InitText(_heading, L"..::Настройки::..", game.assets.font);
        _heading.setStyle(sf::Text::Underlined);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : _options)
        {
            const auto color = _selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));

            if (game.settings.states[option.first])
            {
                option.second.textNode.setStyle(sf::Text::Underlined);
            }

            index++;
        }
    }

    void SettingsMenu::Draw(sf::RenderWindow& window) const
    {
        window.draw(_heading);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void SettingsMenu::OptionSelectHandler(Game& game) const
    {
        auto& isSoundState = game.settings.states[SettingsType::Sound];
        auto& isMusicState = game.settings.states[SettingsType::Music];

        switch (_selectedOptionKey)
        {
        case SettingsType::Sound:
            isSoundState = !isSoundState;

            game.assets.death.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);
            game.assets.menuToggle.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);
            game.assets.menuSelect.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);

            break;
        case SettingsType::Music:
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
        case SettingsType::ResetLeaderboard:
            ClearLeaderboard(game);
            break;
        }
    }

    void SettingsMenu::KeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.assets.menuSelect.play();

                for (auto& option : _options)
                {
                    if (option.first != SettingsType::ResetLeaderboard && option.first == _selectedOptionKey)
                    {
                        const auto& style = option.second.textNode.getStyle();
                        option.second.textNode.setStyle(style == sf::Text::Underlined ? sf::Text::Regular : sf::Text::Underlined);
                        break;
                    }
                }

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
