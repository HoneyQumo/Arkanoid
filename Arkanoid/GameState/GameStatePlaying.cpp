#include "GameStatePlaying.h"
#include "../Application.h"
#include "../Brick.h"
#include "../Shared/Math.h"

namespace ArkanoidGame
{
    void GameStatePlaying::Init(Game& game)
    {
        _gameObjects.emplace_back(std::make_shared<Platform>());
        _gameObjects.emplace_back(std::make_shared<Ball>());
        _gameObjects.emplace_back(std::make_shared<Brick>());

        for (auto&& object : _gameObjects)
        {
            object->Init(game);
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

        platform->Control(*ball, deltaTime);

        if (ball->GetAttached())
        {
            ball->AttachToPlatform(*platform);
            return;
        }

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

        for (auto&& object : _gameObjects)
        {
            const auto brick = dynamic_cast<Brick*>(object.get());

            if (!brick || brick->IsBreaking()) continue;

            if (HasRectCircleCollision(brick->GetSprite(), ball->GetSprite()))
            {
                brick->Hit();

                break;
            }
        }

        _gameObjects.erase(
            std::remove_if(
                _gameObjects.begin(),
                _gameObjects.end(),
                [](const std::shared_ptr<GameObject>& obj)
                {
                    return obj->IsDestroyed();
                }
            ),
            _gameObjects.end()
        );
    }

    void GameStatePlaying::Draw(sf::RenderWindow& window)
    {
        for (auto&& object : _gameObjects)
        {
            object->Draw(window);
        }
    }
}
