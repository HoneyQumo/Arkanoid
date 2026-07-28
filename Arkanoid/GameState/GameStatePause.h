#pragma once
#include <map>
#include "GameStateData.h"
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class GameStatePause : public GameStateData
    {
    public:
        void Init() override;
        void WindowEventHandler(const sf::Event& event) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        enum class OptionKey
        {
            Continue = 0,
            Exit,
        };

        sf::Text _heading;

        std::map<OptionKey, MenuOption> _options = {
            {OptionKey::Continue, {L"Продолжить", {}}},
            {OptionKey::Exit, {L"Выйти в меню", {}}},
        };

        OptionKey _selectedOptionKey = OptionKey::Continue;

        void OptionSelectHandler(Game& game) const;
    };
}
