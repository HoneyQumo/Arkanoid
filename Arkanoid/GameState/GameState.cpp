#include "GameState.h"

#include <assert.h>

#include "GameStateGameOver.h"
#include "GameStatePlaying.h"

namespace ArkanoidGame
{
    GameState::GameState(Type type) : _type(type)
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
        case Type::Pause: { break; }
        case Type::MainMenu: { break; }
        case Type::DifficultyLevel: { break; }
        case Type::Settings: { break; }
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
            _data->Init();
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
