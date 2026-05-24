#pragma once
#include "SFML/Graphics.hpp"
#include "../Settings.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class SettingsMenu
    {
    public:
        void Reset();
        void Init(Game& game);
        void Draw(sf::RenderWindow& window) const;

        void KeyboardHandler(const sf::Event& event, Game& game);

    private:
        sf::Text _heading;

        std::map<Settings::Type, MenuOption> _options = {
            {Settings::Type::Sound, {L"Звук", {}}},
            {Settings::Type::Music, {L"Музыка", {}}},
            {Settings::Type::ResetLeaderboard, {L"Сбросить рекорды", {}}},
        };

        Settings::Type _selectedOptionKey = Settings::Type::Sound;

        void OptionSelectHandler(Game& game) const;
    };
}
