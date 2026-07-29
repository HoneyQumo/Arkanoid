#include "Level.h"
#include "Brick.h"

namespace ArkanoidGame
{
    /* ===== Easy ===== */

    const Level LEVEL_FIRST_STEPS = {
        L"Первые шаги", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....RRRRRRRRRRRR....",
            "....OOOOOOOOOOOO....",
            "....YYYYYYYYYYYY....",
        }
    };

    const Level LEVEL_STAIRS = {
        L"Ступеньки", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "..OOOOOOOOOOOOOOOO..",
            "....YYYYYYYYYYYY....",
        }
    };

    /* ===== EasyMedium ===== */

    const Level LEVEL_PYRAMID = {
        L"Пирамида", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "..OOOOOOOOOOOOOOOO..",
            "....YYYYYYYYYYYY....",
            "......GGGGGGGG......",
        }
    };

    const Level LEVEL_COMB = {
        L"Гребёнка", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "R.R.R.R.R.R.R.R.R.R.",
            "OOOOOOOOOOOOOOOOOOOO",
            "Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.",
            "GGGGGGGGGGGGGGGGGGGG",
        }
    };

    /* ===== Medium ===== */

    const Level LEVEL_RAINBOW = {
        L"Радуга", {
            "....................",
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "....................",
            "....................",
            "OOOOOOOOOOOOOOOOOOOO",
            "....................",
            "....................",
            "YYYYYYYYYYYYYYYYYYYY",
            "....................",
            "....................",
            "GGGGGGGGGGGGGGGGGGGG",
            "....................",
            "....................",
            "BBBBBBBBBBBBBBBBBBBB",
            "....................",
            "....................",
            "PPPPPPPPPPPPPPPPPPPP",
        }
    };

    const Level LEVEL_CHECKERS = {
        L"Шахматы", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "RR..RR..RR..RR..RR..",
            "..OO..OO..OO..OO..OO",
            "YY..YY..YY..YY..YY..",
            "..GG..GG..GG..GG..GG",
            "BB..BB..BB..BB..BB..",
        }
    };

    const Level LEVEL_GATES = {
        L"Ворота", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "OOOO............OOOO",
            "YYYY............YYYY",
            "GGGG............GGGG",
            "BBBBBBBBBBBBBBBBBBBB",
        }
    };

    /* ===== MediumHard ===== */

    const Level LEVEL_FORTRESS = {
        L"Крепость", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "PPPPPPPPPPPPPPPPPPPP",
            "PBBBBBBBBBBBBBBBBBBP",
            "PBGGGGGGGGGGGGGGGGBP",
            "PBGYYYYYYYYYYYYYYGBP",
            "PBGGGGGGGGGGGGGGGGBP",
            "PBBBBBBBBBBBBBBBBBBP",
        }
    };

    const Level LEVEL_DIAGONALS = {
        L"Диагонали", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "RRRR....OOOO....YYYY",
            ".RRRR....OOOO....YYY",
            "..RRRR....OOOO....YY",
            "...RRRR....OOOO....Y",
            "....RRRR....OOOO....",
        }
    };

    const Level LEVEL_HONEYCOMB = {
        L"Соты", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "PP..PP..PP..PP..PP..",
            "..BB..BB..BB..BB..BB",
            "GG..GG..GG..GG..GG..",
            "..YY..YY..YY..YY..YY",
            "OO..OO..OO..OO..OO..",
            "..RR..RR..RR..RR..RR",
        }
    };

    /* ===== Hard ===== */

    const Level LEVEL_WALL = {
        L"Стена", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "OOOOOOOOOOOOOOOOOOOO",
            "YYYYYYYYYYYYYYYYYYYY",
            "GGGGGGGGGGGGGGGGGGGG",
            "BBBBBBBBBBBBBBBBBBBB",
            "PPPPPPPPPPPPPPPPPPPP",
            "RRRRRRRRRRRRRRRRRRRR",
            "OOOOOOOOOOOOOOOOOOOO",
        }
    };

    const Level LEVEL_MAZE = {
        L"Лабиринт", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "PPPPPPPPPPPPPPPPPPPP",
            "P..................P",
            "P.BBBBBBBBBBBBBBBB.P",
            "P.B..............B.P",
            "P.B.GGGGGGGGGGGG.B.P",
            "P.B.G..........G.B.P",
            "P.B.GYYYYYYYYYYG.B.P",
            "P.B.GGGGGGGGGGGG.B.P",
            "P.BBBBBBBBBBBBBBBB.P",
            "PPPPPPPPPPPPPPPPPPPP",
        }
    };

    const Level LEVEL_TARGET = {
        L"Мишень", {
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....................",
            "....RRRRRRRRRRRR....",
            "..RROOOOOOOOOOOORR..",
            "RROOYYYYYYYYYYYYOORR",
            "RROOYYGGGGGGGGYYOORR",
            "RROOYYGGGGGGGGYYOORR",
            "RROOYYYYYYYYYYYYOORR",
            "..RROOOOOOOOOOOORR..",
            "....RRRRRRRRRRRR....",
        }
    };

    const std::map<DifficultyLevel::Type, std::vector<Level>> LEVELS_BY_DIFFICULTY = {
        {DifficultyLevel::Type::Easy, {LEVEL_FIRST_STEPS, LEVEL_STAIRS}},
        {DifficultyLevel::Type::EasyMedium, {LEVEL_STAIRS, LEVEL_PYRAMID, LEVEL_COMB}},
        {DifficultyLevel::Type::Medium, {LEVEL_RAINBOW, LEVEL_CHECKERS, LEVEL_GATES}},
        {DifficultyLevel::Type::MediumHard, {LEVEL_FORTRESS, LEVEL_DIAGONALS, LEVEL_HONEYCOMB}},
        {DifficultyLevel::Type::Hard, {LEVEL_WALL, LEVEL_MAZE, LEVEL_TARGET}},
    };

    const Level& GetLevel(DifficultyLevel::Type difficulty, size_t index)
    {
        return LEVELS_BY_DIFFICULTY.at(difficulty).at(index);
    }

    size_t GetLevelCount(DifficultyLevel::Type difficulty)
    {
        return LEVELS_BY_DIFFICULTY.at(difficulty).size();
    }
}
