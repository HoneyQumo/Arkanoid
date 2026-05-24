#include <cassert>
#include "Game.h"
#include "Application.h"

namespace ArkanoidGame
{
    void Game::ResetState()
    {
        SwitchState(State::MainMenu);
    }

    void Game::PushState(const State& state)
    {
        _gameStateStack.push(state);
    }

    void Game::PopState()
    {
        if (_gameStateStack.size() != 1)
        {
            _gameStateStack.pop();
        }
    }

    void Game::SwitchState(const State& state)
    {
        while (!_gameStateStack.empty())
        {
            _gameStateStack.pop();
        }

        PushState(state);
    }

    Game::State Game::GetState()
    {
        if (!_gameStateStack.empty())
        {
            return _gameStateStack.top();
        }

        return State::MainMenu;
    }

    void Game::Reset(Game& game)
    {
        ResetState();

        /* gui */
        gui.Init(game);

        /* Sounds */
        assets.music.setPlayingOffset(sf::seconds(0.f));
        assets.music.setLoop(true);

        if (settings.GetState(Settings::Type::Music))
        {
            assets.music.play();
        }
        score = 0;
        isWin = false;
    }

    void Game::Init(Game& game)
    {
        /* Fonts */
        assert(assets.font.loadFromFile(RESOURCES_FONTS + "\\pixel_font-7.ttf"));

        /* Graphics */
        // assert(assets.apple.loadFromFile(RESOURCES_GRAPHICS + "\\apple.png"));

        /* Sounds */
        assert(assets.musicBuffer.loadFromFile(RESOURCES_AUDIO + "\\music.wav"));
        assets.music.setBuffer(assets.musicBuffer);
        // assets.music.setVolume(MUSIC_INITIAL_VOLUME);
        assets.music.setVolume(0);

        assert(assets.deathBuffer.loadFromFile(RESOURCES_AUDIO + "\\death.wav"));
        assets.death.setBuffer(assets.deathBuffer);
        assets.death.setVolume(SOUNDS_INITIAL_VOLUME);

        // assert(assets.eatBuffer.loadFromFile(RESOURCES_AUDIO + "\\eat.wav"));
        // assets.eat.setBuffer(assets.eatBuffer);
        // assets.eat.setVolume(SOUNDS_INITIAL_VOLUME);

        assert(assets.menuToggleBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-toggle.wav"));
        assets.menuToggle.setBuffer(assets.menuToggleBuffer);
        assets.menuToggle.setVolume(SOUNDS_INITIAL_VOLUME);

        assert(assets.menuSelectBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-select.wav"));
        assets.menuSelect.setBuffer(assets.menuSelectBuffer);
        assets.menuSelect.setVolume(SOUNDS_INITIAL_VOLUME);

        difficulty.SetDifficultyLevel(DifficultyLevel::Type::Medium);

        leaderboard.DeserializeAndLoad();

        Reset(game);
    }


    void Game::Update(const float& deltaTime)
    {
        const State& gameState = GetState();

        switch (gameState)
        {
        case State::MainMenu:
            break;
        case State::Playing:
            {
                platform.Update(ball, deltaTime);
                ball.Update(platform, deltaTime);

                const auto speed = difficulty.GetValues().speed;

                ball.BounceOffWall(speed);

                if (HasRectCircleCollision(platform.GetShape(), ball.GetShape()) && (ball.GetVelocity().y > 0.f))
                {
                    if (platform.GetSticky())
                    {
                        ball.SetAttached(true);

                        return;
                    }

                    ball.BounceOffPlatform(platform, difficulty.GetValues().speed);
                }
                break;
            }

        case State::GameOver:
            gui.gameOverMenu.Update(Application::Instance().GetGame());

            break;
        case State::Pause:
        case State::DifficultyLevel:
        case State::Settings:
        case State::Leaderboard:
            break;
        }
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        Game& game = Application::Instance().GetGame();
        const State& gameState = GetState();

        switch (gameState)
        {
        case State::MainMenu:
            gui.mainMenu.Draw(window);

            break;
        case State::Playing:
            game.platform.Draw(window);
            game.ball.Draw(window);
            break;

        case State::AskNickname:
            gui.askNicknameMenu.Draw(window);

            break;
        case State::GameOver:
            gui.gameOverMenu.Draw(window);

            break;
        case State::Pause:
            gui.pauseMenu.Draw(window);

            break;
        case State::DifficultyLevel:
            gui.difficultyLevelMenu.Draw(window);

            break;
        case State::Settings:
            gui.settingsMenu.Draw(window);
            break;
        case State::Leaderboard:
            gui.leaderboardMenu.Draw(window);
            break;
        }
    }

    // void Game::ShutdownGame()
    // {
    // }
}
