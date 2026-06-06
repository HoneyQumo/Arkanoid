#include "GUI.h"

namespace ArkanoidGame
{
    void GUI::Init(Game& game)
    {
        mainMenu.Init(game);
        difficultyLevelMenu.Init(game);
        leaderboardMenu.Init(game);
        askNicknameMenu.Init(game);
        settingsMenu.Init(game);
    }
}
