#include "GameStateAskNickname.h"
#include "../Application.h"


namespace ArkanoidGame
{
    void GameStateAskNickname::Init(Game& game)
    {
        _nicknameInput.clear();
        SetOptionKey(_options, _selectedOptionKey, OptionKey::Yes);

        InitText(_heading, std::wstring(L"..::Новый рекорд!::.."), game.assets.font);
        _heading.setStyle(sf::Text::Underlined | sf::Text::Bold);
        _heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        InitText(_subHeading, std::wstring(L"Задать имя?"), game.assets.font, TEXT_HEADING_2);
        _subHeading.setStyle(sf::Text::Bold);
        _subHeading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT);

        InitText(_nicknameText, std::wstring(INPUT_PLACEHOLDER), game.assets.font, TEXT_HEADING_1, sf::Color(50, 50, 50));
        _nicknameText.setStyle(sf::Text::Italic);
        _nicknameText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        int index = 0;
        for (auto& option : _options)
        {
            const auto color = _selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - OFFSET_TOP_WINDOW_10_PERCENT - (_options.size() - index) * 30.f);
            index++;
        }
    }

    void GameStateAskNickname::Draw(sf::RenderWindow& window)
    {
        window.draw(_heading);
        window.draw(_subHeading);
        window.draw(_nicknameText);

        for (const auto& option : _options)
        {
            window.draw(option.second.textNode);
        }
    }

    void GameStateAskNickname::Update(float deltaTime)
    {
    }

    void GameStateAskNickname::WindowEventHandler(const sf::Event& event)
    {
        Game& game = Application::Instance().GetGame();


        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                {
                    game.assets.menuSelect.play();
                    game.leaderboard.Add(game.GetScore(), _nicknameInput);
                    game.leaderboard.SerializeAndSaveGame();
                    game.PopState();
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

        if (event.type == sf::Event::TextEntered)
        {
            if (_nicknameInput == INPUT_PLACEHOLDER)
            {
                _nicknameInput.clear();
            }

            if (event.text.unicode == 8)
            {
                if (!_nicknameInput.isEmpty())
                {
                    _nicknameInput.erase(_nicknameInput.getSize() - 1);
                }
            }
            else if (event.text.unicode < 128 || (event.text.unicode >= 1024 && event.text.unicode <= 1279))
            {
                if (_nicknameInput.getSize() < 20)
                {
                    _nicknameInput += event.text.unicode;
                }
            }

            if (_nicknameInput.isEmpty())
            {
                _nicknameInput = INPUT_PLACEHOLDER;
                _nicknameText.setFillColor(sf::Color(50, 50, 50));
            }
            else
            {
                _nicknameText.setFillColor(sf::Color::White);
            }

            _nicknameText.setString(_nicknameInput.toWideString());
            _nicknameText.setOrigin(GetTextOrigin(_nicknameText, {0.5f, 0.5f}));
        }
    }
}
