#pragma once
#include "AskNicknameMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "DifficultyLevelMenu.h"
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
        LeaderboardMenu leaderboardMenu;
        AskNicknameMenu askNicknameMenu;
        SettingsMenu settingsMenu;

        void Init(Game& game);
    };
}
