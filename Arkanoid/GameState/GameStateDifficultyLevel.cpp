#include "GameStateDifficultyLevel.h"
#include "Core/Application.h"

namespace ArkanoidGame
{
    void GameStateDifficultyLevel::Init(Game& game)
    {
        SetOptionKey(_options, _selectedOptionKey, DifficultyLevel::Type::Easy);

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

        InitHintText(_hint, L"[Up] [Down] Select    [Enter] Apply    [Backspace] Return", game.assets.font);
    }

    void GameStateDifficultyLevel::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }

        window.draw(_hint);
    }

    void GameStateDifficultyLevel::Update(float deltaTime)
    {
    }

    void GameStateDifficultyLevel::WindowEventHandler(const sf::Event& event)
    {
        Game& game = Application::Instance().GetGame();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
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
                    game.GoBack();
                    break;
                }
            }
        }
    }
}
