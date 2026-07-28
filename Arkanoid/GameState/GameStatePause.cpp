#include "GameStatePause.h"

#include "../Application.h"
#include "../Game.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    void GameStatePause::Init()
    {
        const Game& game = Application::Instance().GetGame();

        InitText(_heading, L"..::Пуза::..", game.assets.font);
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

    void GameStatePause::WindowEventHandler(const sf::Event& event)
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
            case sf::Keyboard::Backspace:
                {
                    if (game.GetState() != GameState::Type::AskNickname)
                    {
                        game.PopState();
                    }

                    break;
                }
            case sf::Keyboard::P:
                {
                    game.PopState();
                    break;
                }
            }
        }
    }

    void GameStatePause::Update(float deltaTime)
    {
    }

    void GameStatePause::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void GameStatePause::OptionSelectHandler(Game& game) const
    {
        switch (_selectedOptionKey)
        {
        case OptionKey::Continue:
            game.PopState();
            break;
        case OptionKey::Exit:
            game.Reset(game);
            game.SwitchState(GameState::Type::MainMenu);
            break;
        }
    }
}
