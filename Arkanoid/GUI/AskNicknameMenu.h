#pragma once
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class AskNicknameMenu
    {
    public:
        void Reset();
        void Init(const Game& game);
        void Draw(sf::RenderWindow& window) const;
        void KeyboardHandler(const sf::Event& event, Game& game);
        
        sf::String& GetNicknameInput();

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
