#pragma once
#include <map>
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class PauseMenu
    {
    public:
        enum class OptionKey
        {
            Continue = 0,
            Exit,
        };

        void Reset();
        void Init(const Game& game);
        void Draw(sf::RenderWindow& window) const;

        void OptionSelectHandler(Game& game) const;
        void KeyboardHandler(const sf::Event& event, Game& game);

    private:
        sf::Text _heading;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::Continue, {L"Продолжить", {}}},
            {OptionKey::Exit, {L"Выйти в меню", {}}},
        };

        OptionKey _selectedOptionKey = OptionKey::Continue;
    };
}
