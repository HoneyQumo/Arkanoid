#include "GameState.h"

#include <assert.h>

#include "GameStateAskNickname.h"
#include "GameStateDifficultyLevel.h"
#include "GameStateGameOver.h"
#include "GameStateLeaderboard.h"
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
                _data = std::make_shared<GameStatePlaying>();
                break;
            }
        case Type::GameOver:
            {
                _data = std::make_shared<GameStateGameOver>();
                break;
            }
        case Type::Pause:
            {
                _data = std::make_shared<GameStatePause>();
                break;
            }
        case Type::MainMenu:
            {
                _data = std::make_shared<GameStateMainMenu>();
                break;
            }
        case Type::DifficultyLevel:
            {
                _data = std::make_shared<GameStateDifficultyLevel>();
                break;
            }
        case Type::Settings:
            {
                _data = std::make_shared<GameStateSettings>();
                break;
            }
        case Type::Leaderboard:
            {
                _data = std::make_shared<GameStateLeaderboard>();
                break;
            }
        case Type::AskNickname:
            {
                _data = std::make_shared<GameStateAskNickname>();
                break;
            }
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
