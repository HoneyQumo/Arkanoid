#include "GameStatePlaying.h"
#include "../Application.h"

namespace ArkanoidGame
{
    void GameStatePlaying::Init()
    {
        _gameObjects.emplace_back(std::make_shared<Platform>());
        _gameObjects.emplace_back(std::make_shared<Ball>());

        for (auto&& object : _gameObjects)
        {
            object->Init(Application::Instance().GetGame());
        }
    }

    void GameStatePlaying::WindowEventHandler(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            case sf::Keyboard::P:
                {
                    Application::Instance().GetGame().PushState(GameState::Type::Pause);
                    break;
                }
            }
        }
    }

    void GameStatePlaying::Update(float deltaTime)
    {
        for (auto&& object : _gameObjects)
        {
            object->Update(Application::Instance().GetGame(), deltaTime);
        }

        const auto platform = dynamic_cast<Platform*>(_gameObjects[0].get());
        const auto ball = dynamic_cast<Ball*>(_gameObjects[1].get());

        const Game& game = Application::Instance().GetGame();
        const auto speed = game.difficulty.GetValues().speed;

        ball->BounceOffWall(speed);

        if (HasRectCircleCollision(platform->GetSprite(), ball->GetSprite()) && (ball->GetVelocity().y > 0.f))
        {
            if (platform->GetSticky())
            {
                ball->SetAttached(true);

                return;
            }

            ball->BounceOffPlatform(*platform, speed);
        }
    }

    void GameStatePlaying::Draw(sf::RenderWindow& window)
    {
        for (auto&& object : _gameObjects)
        {
            object->Draw(window);
        }
    }
}
