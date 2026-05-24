#pragma once
#include "AskNicknameMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "DifficultyLevelMenu.h"
#include "GameOverMenu.h"
#include "LeaderboardMenu.h"
#include "SettingsMenu.h"

namespace ArkanoidGame
{
    class GUI
    {
    public:
        MainMenu mainMenu;
        PauseMenu pauseMenu;
        DifficultyLevelMenu difficultyLevelMenu;
        GameOverMenu gameOverMenu;
        LeaderboardMenu leaderboardMenu;
        AskNicknameMenu askNicknameMenu;
        SettingsMenu settingsMenu;
    };
}
