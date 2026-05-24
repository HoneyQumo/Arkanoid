#include "GUI.h"

namespace ArkanoidGame
{
    void GUI::Init(Game& game)
    {
        mainMenu.Init(game);
        pauseMenu.Init(game);
        difficultyLevelMenu.Init(game);
        gameOverMenu.Init(game);
        leaderboardMenu.Init(game);
        askNicknameMenu.Init(game);
        settingsMenu.Init(game);
    }
}
