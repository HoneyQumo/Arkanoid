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

        std::map<SettingsType, MenuOption> _options = {
            {SettingsType::Sound, {L"Звук", {}}},
            {SettingsType::Music, {L"Музыка", {}}},
            {SettingsType::ResetLeaderboard, {L"Сбросить рекорды", {}}},
        };

        SettingsType _selectedOptionKey = SettingsType::Sound;

        void OptionSelectHandler(Game& game) const;
    };
}
