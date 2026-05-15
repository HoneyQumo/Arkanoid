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

        /* GUI */
        GUI.mainMenu.InitMainMenu(game);
        InitPauseMenu(game);
        InitDifficultyLevelMenu(game);
        InitHUD(game);
        InitGameOverMenu(game);
        InitLeaderboardMenu(game);
        InitAskNicknameMenu(game);
        InitSettingsMenu(game);

        /*Sounds*/
        assets.music.setPlayingOffset(sf::seconds(0.f));
        assets.music.setLoop(true);

        if (settings.states[SettingsType::Music])
        {
            assets.music.play();
        }

        /* Game Instances */
        InitField(field);
        InitSnake(snake, assets);

        score = 0;
        isWin = false;
        apples.clear();
        SpawnApple(game);
    }

    void Game::Init(Game& game)
    {
        /* Fonts */
        assert(assets.font.loadFromFile(RESOURCES_FONTS + "\\pixel_font-7.ttf"));

        /* Graphics */
        assert(assets.snakeHead.loadFromFile(RESOURCES_GRAPHICS + "\\head_right.png"));
        assert(assets.snakeBody.loadFromFile(RESOURCES_GRAPHICS + "\\body_horizontal.png"));
        assert(assets.snakeTail.loadFromFile(RESOURCES_GRAPHICS + "\\tail_left.png"));
        assert(assets.apple.loadFromFile(RESOURCES_GRAPHICS + "\\apple.png"));

        /* Sounds */
        assert(assets.musicBuffer.loadFromFile(RESOURCES_AUDIO + "\\music.wav"));
        assets.music.setBuffer(assets.musicBuffer);
        assets.music.setVolume(MUSIC_INITIAL_VOLUME);

        assert(assets.deathBuffer.loadFromFile(RESOURCES_AUDIO + "\\death.wav"));
        assets.death.setBuffer(assets.deathBuffer);
        assets.death.setVolume(SOUNDS_INITIAL_VOLUME);

        assert(assets.eatBuffer.loadFromFile(RESOURCES_AUDIO + "\\eat.wav"));
        assets.eat.setBuffer(assets.eatBuffer);
        assets.eat.setVolume(SOUNDS_INITIAL_VOLUME);

        assert(assets.menuToggleBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-toggle.wav"));
        assets.menuToggle.setBuffer(assets.menuToggleBuffer);
        assets.menuToggle.setVolume(SOUNDS_INITIAL_VOLUME);

        assert(assets.menuSelectBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-select.wav"));
        assets.menuSelect.setBuffer(assets.menuSelectBuffer);
        assets.menuSelect.setVolume(SOUNDS_INITIAL_VOLUME);


        difficulty = {DifficultyLevelType::Medium, LEVEL_CONFIG.at(DifficultyLevelType::Medium)};

        DeserializeAndLoadLeaderboard(leaderboard);

        Reset(game);
    }


    void Game::Update(const float& deltaTime)
    {
        const State& gameState = GetState();
        const float computedDistance = difficulty.value.snakeSpeed * deltaTime;

        switch (gameState)
        {
        case State::MainMenu:
            break;
        case State::Playing:

            if (snake.segments.size() == NUMBER_CELLS * NUMBER_CELLS)
            {
                isWin = true;
                PushState(State::GameOver);
                break;
            }

            SnakeControl(snake);

            if (!snake.awaitingMoveInput)
            {
                UpdateSnake(snake, computedDistance);

                if (HasSnakeCollisionWithWall(snake.segments[0], field) || HasSnakeCollisionWithSelf(snake))
                {
                    assets.music.stop();
                    assets.death.play();
                    PushState(State::GameOver);

                    if (score > 0 && (leaderboard.array.empty() || score > std::prev(leaderboard.array.end())->score))
                    {
                        PushState(State::AskNickname);
                    }

                    break;
                }

                for (unsigned int i = 0; i < apples.size(); ++i)
                {
                    if (
                        GetCoordFromPosition(snake.segments[0].sprite.getPosition()) ==
                        GetCoordFromPosition(apples[i].sprite.getPosition())
                    )
                    {
                        assets.eat.play();
                        score += difficulty.value.pointsPerApple;
                        GrowSnake(snake, assets);
                        apples.clear();
                        SpawnApple(Application::Instance().GetGame());
                    }
                }
            }

            UpdateHUD(Application::Instance().GetGame());

            break;

        case State::GameOver:
            UpdateGameOverMenu(Application::Instance().GetGame());

            break;
        case State::Pause:
        case State::DifficultyLevel:
        case State::Settings:
        case State::Leaderboard:
            break;
        }
    }

    void Game::Draw(sf::RenderWindow& window, const sf::View& HUDView)
    {
        const State& gameState = GetState();

        switch (gameState)
        {
        case State::MainMenu:
            GUI.mainMenu.DrawMainMenu(window);

            break;
        case State::Playing:
            DrawField(window, field);
            DrawApples(window, apples);
            DrawSnake(window, snake);

            window.setView(HUDView);
            DrawHUD(window, GUI.HUD);

            break;

        case State::AskNickname:
            DrawAskNicknameMenu(window, GUI.askNicknameMenu);

            break;
        case State::GameOver:
            DrawGameOverMenu(window, GUI.gameOverMenu);

            break;
        case State::Pause:
            DrawPauseMenu(window, GUI.pauseMenu);

            break;
        case State::DifficultyLevel:
            DrawDifficultyLevelMenu(window, GUI.difficultyLevelMenu);

            break;
        case State::Settings:
            DrawSettingsMenu(window, GUI.settingsMenu);
            break;
        case State::Leaderboard:
            DrawLeaderboardMenu(window, GUI.leaderboardMenu);
            break;
        }
    }

    // void Game::ShutdownGame()
    // {
    // }
}
