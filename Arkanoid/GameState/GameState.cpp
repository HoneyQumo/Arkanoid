#include "GameState.h"

#include <assert.h>

#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePause.h"
#include "GameStatePlaying.h"
#include "GameStateSettings.h"

namespace ArkanoidGame
{
    GameState::GameState(Type type, Game& game) : _type(type)
    {
        switch (type)
        {
        case Type::Playing:
            {
                _data = std::make_unique<GameStatePlaying>();
                break;
            }
        case Type::GameOver:
            {
                _data = std::make_unique<GameStateGameOver>();
                break;
            }
        case Type::Pause:
            {
                _data = std::make_unique<GameStatePause>();
                break;
            }
        case Type::MainMenu:
            {
                _data = std::make_unique<GameStateMainMenu>();
                break;
            }
        case Type::DifficultyLevel: { break; }
        case Type::Settings:
            {
                _data = std::make_unique<GameStateSettings>();
                break;
            }
        case Type::Leaderboard: { break; }
        case Type::AskNickname: { break; }
        default:
            {
                assert(false);
                break;
            }
        }

        if (_data)
        {
            _data->Init(game);
        }
    }

    GameState::~GameState()
    {
        if (_data)
        {
            _data = nullptr;
        }
    }

    void GameState::Update(float timeDelta)
    {
        _data->Update(timeDelta);
    }

    void GameState::Draw(sf::RenderWindow& window) const
    {
        _data->Draw(window);
    }

    void GameState::WindowEventHandler(sf::Event& event)
    {
        _data->WindowEventHandler(event);
    }
}
