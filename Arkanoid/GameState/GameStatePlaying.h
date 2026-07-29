#pragma once
#include "GameStateData.h"
#include "../Platform.h"
#include "../Ball.h"
#include "../GameObject.h"

namespace ArkanoidGame
{
    class GameStatePlaying : public GameStateData
    {
    public:
        void Init(Game& game) override;
        void WindowEventHandler(const sf::Event& event) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        std::vector<std::shared_ptr<GameObject>> _gameObjects;

        sf::Text _hint;
        sf::Text _scoreText;
        sf::Sprite _heartSprite;

        void HandleBallFall(Game& game, Ball& ball, Platform& platform) const;
    };
}
