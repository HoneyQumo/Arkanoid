#pragma once
#include "Objects/PowerUp.h"
#include "Shared/Constants.h"

namespace ArkanoidGame
{
    class Game;
    class GameStatePlaying;

    class IPowerUpCommand
    {
    public:
        virtual ~IPowerUpCommand() = default;

        virtual PowerUp::Type GetType() const = 0;

        virtual float GetDuration() const { return POWERUP_DURATION; }

        virtual void Execute(Game& game, GameStatePlaying& state) = 0;

        virtual void Undo(Game& game, GameStatePlaying& state)
        {
        }
    };

    class ExpandPlatformCommand final : public IPowerUpCommand
    {
    public:
        PowerUp::Type GetType() const override { return PowerUp::Type::Expand; }

        void Execute(Game& game, GameStatePlaying& state) override;
        void Undo(Game& game, GameStatePlaying& state) override;
    };

    class ReducePlatformCommand final : public IPowerUpCommand
    {
    public:
        PowerUp::Type GetType() const override { return PowerUp::Type::Reduce; }

        void Execute(Game& game, GameStatePlaying& state) override;
        void Undo(Game& game, GameStatePlaying& state) override;
    };

    class StickyPlatformCommand final : public IPowerUpCommand
    {
    public:
        PowerUp::Type GetType() const override { return PowerUp::Type::Catch; }

        void Execute(Game& game, GameStatePlaying& state) override;
        void Undo(Game& game, GameStatePlaying& state) override;
    };

    class SlowBallCommand final : public IPowerUpCommand
    {
    public:
        PowerUp::Type GetType() const override { return PowerUp::Type::Slow; }

        void Execute(Game&, GameStatePlaying&) override
        {
        }
    };

    class MultiBallCommand final : public IPowerUpCommand
    {
    public:
        PowerUp::Type GetType() const override { return PowerUp::Type::MultiBall; }
        float GetDuration() const override { return 0.f; }

        void Execute(Game& game, GameStatePlaying& state) override;
    };

    class ExtraLifeCommand final : public IPowerUpCommand
    {
    public:
        PowerUp::Type GetType() const override { return PowerUp::Type::Life; }
        float GetDuration() const override { return 0.f; }

        void Execute(Game& game, GameStatePlaying& state) override;
    };
}
