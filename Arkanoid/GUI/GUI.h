#pragma once
#include "AskNicknameMenu.h"
#include "MainMenu.h"
#include "DifficultyLevelMenu.h"
#include "LeaderboardMenu.h"
#include "SettingsMenu.h"

namespace ArkanoidGame
{
    class GUI
    {
    public:
        MainMenu mainMenu;
        DifficultyLevelMenu difficultyLevelMenu;
        LeaderboardMenu leaderboardMenu;
        AskNicknameMenu askNicknameMenu;
        SettingsMenu settingsMenu;

        void Init(Game& game);
    };
}
