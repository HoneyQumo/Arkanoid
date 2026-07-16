#pragma once
#include "GameStateData.h"
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"


namespace ArkanoidGame
{
    class GameStateAskNickname : public GameStateData
    {
    public:
        void Init() override;
        void Draw(sf::RenderWindow& window) override;
        void WindowEventHandler(const sf::Event& event) override;

        sf::String& GetNicknameInput() { return _nicknameInput; }

    private:
        enum class OptionKey
        {
            Yes = 0,
            No
        };

        sf::Text _heading;
        sf::Text _subHeading;

        sf::String _nicknameInput;
        sf::Text _nicknameText;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::Yes, {L"Да", {}}},
            {OptionKey::No, {L"Нет", {}}},
        };

        OptionKey _selectedOptionKey = OptionKey::No;
    };
}
