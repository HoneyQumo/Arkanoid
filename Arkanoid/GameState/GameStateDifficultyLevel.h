#pragma once
#include "GameStateData.h"
#include "SFML/Graphics.hpp"
#include "../DifficultyLevel.h"
#include "../Shared/Shared.h"

namespace ArkanoidGame
{
    class Game;

    class GameStateDifficultyLevel : public GameStateData
    {
    public:
        void Init(Game& game) override;
        void Draw(sf::RenderWindow& window) override;
        void Update(float deltaTime) override;
        void WindowEventHandler(const sf::Event& event) override;

    private:
        sf::Text _heading;

        std::map<DifficultyLevel::Type, MenuOption> _options = {
            {DifficultyLevel::Type::Easy, {L"Простой", {}}},
            {DifficultyLevel::Type::EasyMedium, {L"Тяжелее простого", {}}},
            {DifficultyLevel::Type::Medium, {L"Средний", {}}},
            {DifficultyLevel::Type::MediumHard, {L"Легче тяжелого", {}}},
            {DifficultyLevel::Type::Hard, {L"Тяжелый", {}}},
        };

        DifficultyLevel::Type _selectedOptionKey = DifficultyLevel::Type::Easy;
    };
}
