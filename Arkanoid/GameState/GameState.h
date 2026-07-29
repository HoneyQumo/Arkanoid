#pragma once
#include <algorithm>
#include <memory>
#include "GameStateData.h"

namespace ArkanoidGame
{
    class Game;

    class GameState
    {
    public:
        enum class Type
        {
            Playing = 0,
            GameOver,
            Pause,
            MainMenu,
            DifficultyLevel,
            Settings,
            Leaderboard,
            AskNickname
        };

        GameState() = default;
        GameState(Type type, Game& game);
        GameState(const GameState& state) = delete;
        GameState(GameState&& state) { operator=(std::move(state)); }

        ~GameState();

        GameState& operator=(const GameState& state) = delete;

        GameState& operator=(GameState&& state) noexcept
        {
            _type = state._type;
            _data = std::move(state._data);
            state._data = nullptr;
            return *this;
        }

        Type GetType() const { return _type; }

        void Update(float timeDelta);
        void Draw(sf::RenderWindow& window) const;
        void WindowEventHandler(sf::Event& event);

    private:
        Type _type = Type::MainMenu;
        std::unique_ptr<GameStateData> _data = nullptr;
    };
}
