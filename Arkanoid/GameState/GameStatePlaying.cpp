#include "GameStatePlaying.h"

#include <algorithm>

#include "../Application.h"
#include "../Brick.h"
#include "../Shared/Math.h"
#include "../Shared/Shared.h"
#include "../Level.h"

namespace ArkanoidGame
{
    void GameStatePlaying::Init(Game& game)
    {
        _platform = std::make_shared<Platform>();
        _gameObjects.emplace_back(_platform);
        _gameObjects.emplace_back(std::make_shared<Ball>());

        const auto& level = GetLevel(game.difficulty.GetType(), game.GetLevelIndex());

        for (size_t row = 0; row < level.grid.size(); ++row)
        {
            for (size_t col = 0; col < level.grid[row].size(); ++col)
            {
                const char symbol = level.grid[row][col];

                if (symbol == '.') continue;

                _gameObjects.emplace_back(std::make_shared<Brick>(
                    Brick::GetKindByLevelSymbol(symbol),
                    Brick::GetColorByLevelSymbol(symbol),
                    sf::Vector2f(static_cast<float>(col) * BRICK_WIDTH, static_cast<float>(row) * BRICK_HEIGHT)));
            }
        }

        for (auto&& object : _gameObjects)
        {
            object->Init(game);
        }

        InitHintText(_hint, L"[A] [D] Move    [RMB] Mouse    [Space] [LMB] Launch    [Esc] Pause", game.assets.font);

        InitText(_scoreText, "0", game.assets.font, TEXT_MENU_ITEM, sf::Color::White, {1.f, 0.5f});
        _scoreText.setPosition(SCREEN_WIDTH - HUD_MARGIN_SIDE, HUD_Y_POSITION);

        InitText(_comboText, "", game.assets.font, TEXT_MENU_ITEM, COMBO_COLOR, {1.f, 0.5f});

        _heartSprite = sf::Sprite(game.assets.heart);
        SetSpriteSize(_heartSprite, HEART_SIZE, HEART_SIZE);
        SetSpriteOrigin(_heartSprite, {0.f, 0.5f});

        _powerUpIcon = sf::Sprite(game.assets.powerups);
        _powerUpIcon.setTextureRect(PowerUp::GetIconRect(PowerUp::Type::Expand));
        SetSpriteSize(_powerUpIcon, HUD_POWERUP_WIDTH, HUD_POWERUP_HEIGHT);
        SetSpriteOrigin(_powerUpIcon, {0.f, 0.5f});
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
                    ReleaseMouse();
                    Application::Instance().GetGame().PushState(GameState::Type::Pause);
                    break;
                }
            }
        }
    }

    void GameStatePlaying::Update(float deltaTime)
    {
        Game& game = Application::Instance().GetGame();

        /* Origin пересчитывается каждый раз: он зависит от ширины строки */
        _scoreText.setString(std::to_string(game.GetScore()));
        _scoreText.setOrigin(GetTextOrigin(_scoreText, {1.f, 0.5f}));

        if (_combo >= COMBO_MIN_TO_SHOW)
        {
            _comboText.setString("+" + std::to_string(_combo));
            _comboText.setOrigin(GetTextOrigin(_comboText, {1.f, 0.5f}));
            _comboText.setPosition(
                _scoreText.getPosition().x - _scoreText.getLocalBounds().width - COMBO_GAP,
                HUD_Y_POSITION);
        }

        UpdateEffects(game, deltaTime);

        for (auto&& object : _gameObjects)
        {
            object->Update(game, deltaTime);
        }

        _platform->Control(deltaTime);

        const auto difficultyValues = game.difficulty.GetValues();
        const float ballSpeed = IsEffectActive(PowerUp::Type::Slow)
                                    ? difficultyValues.speed * POWERUP_SLOW_FACTOR
                                    : difficultyValues.speed;

        auto balls = CollectBalls();

        LaunchAttachedBalls(balls);

        for (const auto& ball : balls)
        {
            if (ball->GetAttached())
            {
                ball->AttachToPlatform(*_platform);
                continue;
            }

            ball->BounceOffWall(ballSpeed);

            if (ball->IsFallen()) continue;

            if (_platform->CheckCollision(ball))
            {
                /* Касание платформы сбрасывает комбо */
                _combo = 0;

                if (ball->GetAttached()) continue;

                ball->BounceOffPlatform(*_platform, ballSpeed);
            }

            HandleBrickCollisions(game, ball, difficultyValues);
        }

        CollectPowerUps(game);

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

        if (CollectBalls().empty())
        {
            HandleAllBallsLost(game);
            return;
        }

        if (!HasBreakableBricks())
        {
            ReleaseMouse();
            game.SetWin(true);
            game.PushState(GameState::Type::GameOver);
        }
    }

    std::vector<std::shared_ptr<Ball>> GameStatePlaying::CollectBalls() const
    {
        std::vector<std::shared_ptr<Ball>> balls;

        for (auto&& object : _gameObjects)
        {
            if (const auto ball = std::dynamic_pointer_cast<Ball>(object))
            {
                balls.push_back(ball);
            }
        }

        return balls;
    }

    bool GameStatePlaying::HasBreakableBricks() const
    {
        return std::any_of(
            _gameObjects.begin(),
            _gameObjects.end(),
            [](const std::shared_ptr<GameObject>& obj)
            {
                const auto brick = dynamic_cast<const Brick*>(obj.get());
                /* Неразрушимые кирпичи остаются на поле навсегда,
                   иначе уровень было бы невозможно пройти */
                return brick != nullptr && !brick->IsUnbreakable();
            });
    }

    bool GameStatePlaying::IsEffectActive(const PowerUp::Type type) const
    {
        return _activeEffects.find(type) != _activeEffects.end();
    }

    void GameStatePlaying::LaunchAttachedBalls(const std::vector<std::shared_ptr<Ball>>& balls)
    {
        const bool isLaunchRequested = sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
            || sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (!isLaunchRequested) return;

        bool hasLaunched = false;

        for (const auto& ball : balls)
        {
            if (!ball->GetAttached()) continue;

            ball->Launch();
            hasLaunched = true;
        }

        if (hasLaunched && !IsEffectActive(PowerUp::Type::Catch))
        {
            _platform->SetSticky(false);
        }
    }

    void GameStatePlaying::HandleBrickCollisions(Game& game, const std::shared_ptr<Ball>& ball, const DifficultyLevel::Values& values)
    {
        std::shared_ptr<Brick> destroyed;

        for (auto&& object : _gameObjects)
        {
            const auto brick = std::dynamic_pointer_cast<Brick>(object);

            if (!brick) continue;

            if (!brick->CheckCollision(ball)) continue;

            ball->BounceOffRect(brick->GetBounds());

            if (brick->IsBreaking())
            {
                destroyed = brick;
            }

            break;
        }

        if (!destroyed) return;

        game.assets.destroy.play();

        ++_combo;
        const unsigned comboBonus = (_combo - 1) * values.comboBonus;
        game.SetScore(game.GetScore() + values.pointsRate + comboBonus);

        if (GetIntegerInRange(0, 999) < static_cast<int>(POWERUP_DROP_CHANCE * 1000.f))
        {
            const auto bounds = destroyed->GetBounds();

            auto powerUp = std::make_shared<PowerUp>(
                PowerUp::GetRandomType(),
                sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f));

            powerUp->Init(game);
            _gameObjects.emplace_back(powerUp);
        }
    }

    void GameStatePlaying::CollectPowerUps(Game& game)
    {
        std::vector<PowerUp::Type> collected;

        for (auto&& object : _gameObjects)
        {
            const auto powerUp = std::dynamic_pointer_cast<PowerUp>(object);

            if (!powerUp) continue;

            if (!powerUp->CheckCollision(_platform)) continue;

            collected.push_back(powerUp->GetType());
        }

        for (const auto type : collected)
        {
            game.assets.menuSelect.play();
            ApplyPowerUp(game, type);
        }
    }

    void GameStatePlaying::ApplyPowerUp(Game& game, const PowerUp::Type type)
    {
        switch (type)
        {
        case PowerUp::Type::Expand:
            {
                _activeEffects.erase(PowerUp::Type::Reduce);
                _activeEffects[PowerUp::Type::Expand] = POWERUP_DURATION;
                ApplyPlatformWidth();
                break;
            }
        case PowerUp::Type::Reduce:
            {
                _activeEffects.erase(PowerUp::Type::Expand);
                _activeEffects[PowerUp::Type::Reduce] = POWERUP_DURATION;
                ApplyPlatformWidth();
                break;
            }
        case PowerUp::Type::Catch:
            {
                _activeEffects[PowerUp::Type::Catch] = POWERUP_DURATION;
                _platform->SetSticky(true);
                break;
            }
        case PowerUp::Type::Slow:
            {
                _activeEffects[PowerUp::Type::Slow] = POWERUP_DURATION;
                break;
            }
        case PowerUp::Type::MultiBall:
            {
                SpawnExtraBalls(game, CollectBalls());
                break;
            }
        case PowerUp::Type::Life:
            {
                game.SetLives(game.GetLives() + 1);
                break;
            }
        }
    }

    void GameStatePlaying::UpdateEffects(Game& game, const float deltaTime)
    {
        bool isPlatformWidthChanged = false;

        for (auto it = _activeEffects.begin(); it != _activeEffects.end();)
        {
            it->second -= deltaTime;

            if (it->second > 0.f)
            {
                ++it;
                continue;
            }

            const PowerUp::Type expired = it->first;
            it = _activeEffects.erase(it);

            if (expired == PowerUp::Type::Expand || expired == PowerUp::Type::Reduce)
            {
                isPlatformWidthChanged = true;
            }
            else if (expired == PowerUp::Type::Catch)
            {
                _platform->SetSticky(false);
            }
        }

        if (isPlatformWidthChanged)
        {
            ApplyPlatformWidth();
        }
    }

    void GameStatePlaying::ApplyPlatformWidth()
    {
        if (IsEffectActive(PowerUp::Type::Expand))
        {
            _platform->SetWidth(PLATFORM_WIDTH_EXPANDED);
        }
        else if (IsEffectActive(PowerUp::Type::Reduce))
        {
            _platform->SetWidth(PLATFORM_WIDTH_REDUCED);
        }
        else
        {
            _platform->SetWidth(PLATFORM_WIDTH);
        }
    }

    void GameStatePlaying::SpawnExtraBalls(Game& game, const std::vector<std::shared_ptr<Ball>>& balls)
    {
        if (balls.empty()) return;

        const auto& source = balls.front();
        const auto position = source->GetSprite().getPosition();
        auto velocity = source->GetVelocity();

        if (velocity.x == 0.f && velocity.y == 0.f)
        {
            velocity = {0.f, -game.difficulty.GetValues().speed};
        }

        for (unsigned i = 1; i <= MULTIBALL_EXTRA_COUNT; ++i)
        {
            const float angle = MULTIBALL_SPREAD_RADIANS * static_cast<float>(i)
                * (i % 2 == 0 ? -1.f : 1.f);

            auto extra = std::make_shared<Ball>();
            extra->Init(game);
            extra->GetSprite().setPosition(position);
            extra->SetAttached(false);
            extra->SetVelocity(RotateVector(velocity, angle));

            _gameObjects.emplace_back(extra);
        }
    }

    void GameStatePlaying::HandleAllBallsLost(Game& game)
    {
        game.assets.death.play();
        _combo = 0;

        const unsigned livesLeft = game.GetLives() > 0 ? game.GetLives() - 1 : 0;
        game.SetLives(livesLeft);

        if (livesLeft == 0)
        {
            ReleaseMouse();
            game.SetWin(false);
            game.PushState(GameState::Type::GameOver);
            return;
        }

        auto ball = std::make_shared<Ball>();
        ball->Init(game);
        _gameObjects.emplace_back(ball);

        _platform->SetSticky(true);
    }

    void GameStatePlaying::Draw(sf::RenderWindow& window)
    {
        for (auto&& object : _gameObjects)
        {
            object->Draw(window);
        }

        const unsigned lives = Application::Instance().GetGame().GetLives();

        for (unsigned i = 0; i < lives; ++i)
        {
            _heartSprite.setPosition(
                HUD_MARGIN_SIDE + static_cast<float>(i) * (HEART_SIZE + HEART_GAP),
                HUD_Y_POSITION);

            window.draw(_heartSprite);
        }

        float iconX = HUD_POWERUP_LEFT;

        for (const auto& effect : _activeEffects)
        {
            _powerUpIcon.setTextureRect(PowerUp::GetIconRect(effect.first));
            _powerUpIcon.setPosition(iconX, HUD_Y_POSITION);
            window.draw(_powerUpIcon);

            iconX += HUD_POWERUP_WIDTH + HEART_GAP;
        }

        window.draw(_scoreText);

        if (_combo >= COMBO_MIN_TO_SHOW)
        {
            window.draw(_comboText);
        }

        window.draw(_hint);
    }

    void GameStatePlaying::ReleaseMouse()
    {
        auto& window = Application::Instance().GetWindow();

        window.setMouseCursorVisible(true);
        window.setMouseCursorGrabbed(false);
    }
}
