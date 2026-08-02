#include "Objects/PowerUpCommands.h"

#include "Core/Game.h"
#include "GameState/GameStatePlaying.h"
#include "Objects/Platform.h"

namespace ArkanoidGame
{
    void ExpandPlatformCommand::Execute(Game&, GameStatePlaying& state)
    {
        state.CancelEffect(PowerUp::Type::Reduce);
        state.GetPlatform().SetWidth(PLATFORM_WIDTH_EXPANDED);
    }

    void ExpandPlatformCommand::Undo(Game&, GameStatePlaying& state)
    {
        state.GetPlatform().SetWidth(PLATFORM_WIDTH);
    }

    void ReducePlatformCommand::Execute(Game&, GameStatePlaying& state)
    {
        state.CancelEffect(PowerUp::Type::Expand);
        state.GetPlatform().SetWidth(PLATFORM_WIDTH_REDUCED);
    }

    void ReducePlatformCommand::Undo(Game&, GameStatePlaying& state)
    {
        state.GetPlatform().SetWidth(PLATFORM_WIDTH);
    }

    void StickyPlatformCommand::Execute(Game&, GameStatePlaying& state)
    {
        state.GetPlatform().SetSticky(true);
    }

    void StickyPlatformCommand::Undo(Game&, GameStatePlaying& state)
    {
        state.GetPlatform().SetSticky(false);
    }

    void MultiBallCommand::Execute(Game& game, GameStatePlaying& state)
    {
        state.SpawnExtraBalls(game);
    }

    void ExtraLifeCommand::Execute(Game& game, GameStatePlaying&)
    {
        game.SetLives(game.GetLives() + 1);
    }
}
