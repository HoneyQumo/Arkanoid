#include "../Game.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    void DifficultyLevelMenu::Reset()
    {
        SetOptionKey(_options, _selectedOptionKey, DifficultyLevel::Type::Easy);
    }

    void DifficultyLevelMenu::Init(const Game& game)
    {
        Reset();

        InitText(_heading, L"..::Сложность::..", game.assets.font);
        _heading.setStyle(sf::Text::Underlined);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : _options)
        {
            const auto color = _selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));

            if (game.difficulty.GetType() == option.first)
            {
                option.second.textNode.setStyle(sf::Text::Underlined);
            }

            index++;
        }
    }

    void DifficultyLevelMenu::Draw(sf::RenderWindow& window) const
    {
        window.draw(_heading);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void DifficultyLevelMenu::KeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.assets.menuSelect.play();
                game.difficulty.SetDifficultyLevel(_selectedOptionKey);

                for (auto& option : _options)
                {
                    if (option.first == game.difficulty.GetType())
                    {
                        option.second.textNode.setStyle(sf::Text::Underlined);
                    }
                    else
                    {
                        option.second.textNode.setStyle(sf::Text::Regular);
                    }
                }
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
