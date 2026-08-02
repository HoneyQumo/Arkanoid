#pragma once
#include <vector>
#include "GameStateData.h"
#include "Data/DifficultyLevel.h"
#include "Objects/Platform.h"
#include "Objects/Ball.h"
#include "Objects/PowerUp.h"
#include "Objects/PowerUpCommands.h"
#include "Objects/GameObject.h"
#include "Shared/Constants.h"
#include "Shared/Observer.h"

namespace ArkanoidGame
{
    class GameStatePlaying : public GameStateData,
                             public IObserver,
                             public std::enable_shared_from_this<GameStatePlaying>
    {
    public:
        void Init(Game& game) override;
        void WindowEventHandler(const sf::Event& event) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

        void Notify(std::shared_ptr<IObservable> observable, ObservableEvent event) override;

        Platform& GetPlatform() { return *_platform; }
        void SpawnExtraBalls(Game& game);
        void CancelEffect(PowerUp::Type type);

    private:
        struct ActivePowerUp
        {
            std::shared_ptr<IPowerUpCommand> command;
            float timeLeft = 0.f;
        };

        std::vector<std::shared_ptr<GameObject>> _gameObjects;

        std::shared_ptr<Platform> _platform;

        std::vector<ActivePowerUp> _activePowerUps;

        sf::Text _hint;
        sf::Text _scoreText;
        sf::Text _comboText;
        sf::Sprite _heartSprite;
        sf::Sprite _powerUpIcon;

        sf::Text _debugBallSpeedText;
        bool _debugShowBallSpeed = DEBUG_SHOW_BALL_SPEED;

        unsigned _combo = 0;

        unsigned _breakableBricksLeft = 0;
        unsigned _ballsInPlay = 0;

        std::shared_ptr<Ball> SpawnBall();
        std::vector<Ball*> CollectBalls() const;
        bool IsEffectActive(PowerUp::Type type) const;

        void LaunchAttachedBalls(const std::vector<Ball*>& balls);
        void HandleBrickCollisions(Game& game, Ball& ball, const DifficultyLevel::Values& values);
        void CollectPowerUps(Game& game);
        void ActivatePowerUp(Game& game, const std::shared_ptr<IPowerUpCommand>& command);
        void UpdateEffects(Game& game, float deltaTime);
        void HandleAllBallsLost(Game& game);
    };
}
