#pragma once
#include "GameStateData.h"
#include "SFML/Graphics.hpp"
#include "Shared/Menu.h"


namespace ArkanoidGame
{
    class Game;

    class GameStateAskNickname : public GameStateData
    {
    public:
        void Init(Game& game) override;
        void Draw(sf::RenderWindow& window) override;
        void Update(float deltaTime) override;
        void WindowEventHandler(const sf::Event& event) override;

    private:
        enum class OptionKey
        {
            Yes = 0,
            No
        };

        sf::Text _heading;
        sf::Text _subHeading;
        sf::Text _hint;

        sf::String _nicknameInput;
        sf::Text _nicknameText;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::Yes, {L"Да", {}}},
            {OptionKey::No, {L"Нет", {}}},
        };

        OptionKey _selectedOptionKey = OptionKey::No;
    };
}
