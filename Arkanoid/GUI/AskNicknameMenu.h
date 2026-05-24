#pragma once
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class AskNicknameMenu
    {
    public:
        enum class AskNicknameMenuOptionKey
        {
            Yes = 0,
            No
        };

        void Reset();
        void Init(const Game& game);
        void Draw(sf::RenderWindow& window) const;
        void KeyboardHandler(const sf::Event& event, Game& game);
        
        sf::String& GetNicknameInput();

    private:
        sf::Text _heading;
        sf::Text _subHeading;

        sf::String _nicknameInput;
        sf::Text _nicknameText;

        std::map<AskNicknameMenuOptionKey, MenuOption> _options = {
            {AskNicknameMenuOptionKey::Yes, {L"Да", {}}},
            {AskNicknameMenuOptionKey::No, {L"Нет", {}}},
        };

        AskNicknameMenuOptionKey _selectedOptionKey = AskNicknameMenuOptionKey::No;
    };
}
