#include "GameStatePlaying.h"
#include "../Application.h"
#include "../Brick.h"
#include "../Shared/Math.h"
#include "../Shared/Shared.h"
#include "../Level.h"

namespace ArkanoidGame
{
    void GameStatePlaying::Init(Game& game)
    {
        _gameObjects.emplace_back(std::make_shared<Platform>());
        _gameObjects.emplace_back(std::make_shared<Ball>());


        const auto& level = GetLevel(game.difficulty.GetType(), game.GetLevelIndex());

        for (size_t row = 0; row < level.grid.size(); ++row)
        {
            for (size_t col = 0; col < level.grid[row].size(); ++col)
            {
                const char symbol = level.grid[row][col];

                if (symbol == '.') continue;

                const auto brickColor = Brick::GetColorByLevelSymbol(symbol);
                auto brick = std::make_shared<Brick>(
                    brickColor,
                    sf::Vector2f(static_cast<float>(col) * BRICK_WIDTH, static_cast<float>(row) * BRICK_HEIGHT));

                _gameObjects.emplace_back(brick);
            }
        }

        for (auto&& object : _gameObjects)
        {
            object->Init(game);
        }

        InitHintText(_hint, L"[A] [D] Move    [RMB] Mouse    [Space] Launch    [Esc] Pause", game.assets.font);

        InitText(_scoreText, "0", game.assets.font, TEXT_MENU_ITEM, sf::Color::White, {1.f, 0.5f});
        _scoreText.setPosition(SCREEN_WIDTH - HUD_MARGIN_SIDE, HUD_Y_POSITION);

        InitText(_comboText, "", game.assets.font, TEXT_MENU_ITEM, COMBO_COLOR, {1.f, 0.5f});

        _heartSprite = sf::Sprite(game.assets.heart);
        SetSpriteSize(_heartSprite, HEART_SIZE, HEART_SIZE);
        SetSpriteOrigin(_heartSprite, {0.f, 0.5f});
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
        Game& game = Application::Instance().GetGame();

        /* Origin пересчитывается каждый раз: он зависит от ширины строки */
        _scoreText.setString(std::to_string(game.GetScore()));
        _scoreText.setOrigin(GetTextOrigin(_scoreText, {1.f, 0.5f}));

        if (_combo >= COMBO_MIN_TO_SHOW)
        {
            _comboText.setString("+" + std::to_string(_combo));
            _comboText.setOrigin(GetTextOrigin(_comboText, {1.f, 0.5f}));

            /* Прижимаем к счёту слева, с учётом его текущей ширины */
            _comboText.setPosition(
                _scoreText.getPosition().x - _scoreText.getLocalBounds().width - COMBO_GAP,
                HUD_Y_POSITION);
        }

        for (auto&& object : _gameObjects)
        {
            object->Update(game, deltaTime);
        }

        const auto platform = dynamic_cast<Platform*>(_gameObjects[0].get());
        const auto ball = dynamic_cast<Ball*>(_gameObjects[1].get());

        platform->Control(*ball, deltaTime);

        if (ball->GetAttached())
        {
            ball->AttachToPlatform(*platform);
            return;
        }

        const auto difficultyValues = game.difficulty.GetValues();

        ball->BounceOffWall(difficultyValues.speed);

        if (ball->IsFallen())
        {
            HandleBallFall(game, *ball, *platform);
            return;
        }

        if (HasRectCircleCollision(platform->GetSprite(), ball->GetSprite()) && (ball->GetVelocity().y > 0.f))
        {
            _combo = 0;

            if (platform->GetSticky())
            {
                ball->SetAttached(true);

                return;
            }

            ball->BounceOffPlatform(*platform, difficultyValues.speed);
        }

        for (auto&& object : _gameObjects)
        {
            const auto brick = dynamic_cast<Brick*>(object.get());

            if (!brick || brick->IsBreaking()) continue;

            if (HasRectCircleCollision(brick->GetSprite(), ball->GetSprite()))
            {
                brick->Hit();
                ball->BounceOffRect(brick->GetSprite());
                game.assets.destroy.play();

                ++_combo;
                const unsigned comboBonus = (_combo - 1) * difficultyValues.comboBonus;
                game.SetScore(game.GetScore() + difficultyValues.pointsRate + comboBonus);

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

        const bool hasBricks = std::any_of(
            _gameObjects.begin(),
            _gameObjects.end(),
            [](const std::shared_ptr<GameObject>& obj)
            {
                return dynamic_cast<const Brick*>(obj.get()) != nullptr;
            });

        if (!hasBricks)
        {
            game.SetWin(true);
            game.PushState(GameState::Type::GameOver);
        }
    }

    void GameStatePlaying::HandleBallFall(Game& game, Ball& ball, Platform& platform)
    {
        game.assets.death.play();
        _combo = 0;

        const unsigned livesLeft = game.GetLives() > 0 ? game.GetLives() - 1 : 0;
        game.SetLives(livesLeft);

        if (livesLeft == 0)
        {
            game.SetWin(false);
            game.PushState(GameState::Type::GameOver);
            return;
        }

        ball.Respawn();
        platform.SetSticky(true);
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

        window.draw(_scoreText);

        if (_combo >= COMBO_MIN_TO_SHOW)
        {
            window.draw(_comboText);
        }

        window.draw(_hint);
    }
}
