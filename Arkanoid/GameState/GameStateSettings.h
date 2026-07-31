#pragma once
#include "GameStateData.h"
#include "Core/Settings.h"
#include "Core/Application.h"
#include "Shared/Menu.h"

namespace ArkanoidGame
{
    class Game;

    class GameStateSettings : public GameStateData
    {
    public:
        void Init(Game& game) override;
        void WindowEventHandler(const sf::Event& event) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        sf::Text _heading;
        sf::Text _hint;

        std::map<Settings::Type, MenuOption> _options = {
            {Settings::Type::Sound, {L"Звук", {}}},
            {Settings::Type::Music, {L"Музыка", {}}},
            {Settings::Type::ResetLeaderboard, {L"Сбросить рекорды", {}}},
        };

        Settings::Type _selectedOptionKey = Settings::Type::Sound;

        void OptionSelectHandler(Game& game) const;
    };
}
