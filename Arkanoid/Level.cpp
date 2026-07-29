#include <map>
#include "Level.h"

namespace ArkanoidGame
{
    /* Сетка: 20 колонок, строка = 20 символов.
       Первая пустая строка задаёт отступ от верхнего края экрана. */

    /* ===== Easy ===== */

    const Level LEVEL_FIRST_STEPS = {
        L"Первые шаги", {
            "....................",
            "....................",
            "......RRRRRRRR......",
            "......RRRRRRRR......",
            "....................",
            "....................",
            "....OOOOOOOOOOOO....",
            "....OOOOOOOOOOOO....",
            "....................",
            "....................",
            "..YYYYYYYYYYYYYYYY..",
            "..YYYYYYYYYYYYYYYY..",
        }
    };

    const Level LEVEL_STAIRS = {
        L"Ступеньки", {
            "....................",
            "RRRR................",
            "RRRR................",
            "..OOOO..............",
            "..OOOO..............",
            "....YYYY............",
            "....YYYY............",
            "......GGGG..........",
            "......GGGG..........",
            "........BBBB........",
            "........BBBB........",
            "..........PPPP......",
            "..........PPPP......",
            "............RRRR....",
            "............RRRR....",
            "..............OOOO..",
            "..............OOOO..",
            "................YYYY",
        }
    };

    const Level LEVEL_CLOUDS = {
        L"Облака", {
            "....................",
            "..BBB......BBB......",
            "..BBB......BBB......",
            "....................",
            ".......YYYY.........",
            ".......YYYY.........",
            "....................",
            "...GG.........GG....",
            "...GG.........GG....",
            "....................",
            ".....OOOOOOOOOO.....",
            ".....OOOOOOOOOO.....",
            "....................",
            "PP................PP",
        }
    };

    /* ===== EasyMedium ===== */

    const Level LEVEL_PYRAMID = {
        L"Пирамида", {
            "....................",
            ".........RR.........",
            "........OOOO........",
            ".......YYYYYY.......",
            "......GGGGGGGG......",
            ".....BBBBBBBBBB.....",
            "....PPPPPPPPPPPP....",
            "...RRRRRRRRRRRRRR...",
            "..OOOOOOOOOOOOOOOO..",
            ".YYYYYYYYYYYYYYYYYY.",
            "GGGGGGGGGGGGGGGGGGGG",
        }
    };

    const Level LEVEL_COMB = {
        L"Гребёнка", {
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "R.R.R.R.R.R.R.R.R.R.",
            "R.R.R.R.R.R.R.R.R.R.",
            "OOOOOOOOOOOOOOOOOOOO",
            ".O.O.O.O.O.O.O.O.O.O",
            ".O.O.O.O.O.O.O.O.O.O",
            "YYYYYYYYYYYYYYYYYYYY",
            "Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.",
            "Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.",
            "GGGGGGGGGGGGGGGGGGGG",
            ".G.G.G.G.G.G.G.G.G.G",
            ".G.G.G.G.G.G.G.G.G.G",
            "BBBBBBBBBBBBBBBBBBBB",
        }
    };

    const Level LEVEL_WAVE = {
        L"Волна", {
            "....................",
            "RRRRR..........RRRRR",
            ".RRRRR........RRRRR.",
            "..OOOOO......OOOOO..",
            "...OOOOO....OOOOO...",
            "....YYYYY..YYYYY....",
            ".....YYYYYYYYYY.....",
            "....GGGGG..GGGGG....",
            "...GGGGG....GGGGG...",
            "..BBBBB......BBBBB..",
            ".BBBBB........BBBBB.",
            "PPPPP..........PPPPP",
        }
    };

    /* ===== Medium ===== */

    const Level LEVEL_RAINBOW = {
        L"Радуга", {
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "RRRRRRRRRRRRRRRRRRRR",
            "OOOOOOOOOOOOOOOOOOOO",
            "OOOOOOOOOOOOOOOOOOOO",
            "YYYYYYYYYYYYYYYYYYYY",
            "YYYYYYYYYYYYYYYYYYYY",
            "GGGGGGGGGGGGGGGGGGGG",
            "GGGGGGGGGGGGGGGGGGGG",
            "BBBBBBBBBBBBBBBBBBBB",
            "BBBBBBBBBBBBBBBBBBBB",
            "PPPPPPPPPPPPPPPPPPPP",
            "PPPPPPPPPPPPPPPPPPPP",
        }
    };

    const Level LEVEL_CHECKERS = {
        L"Шахматы", {
            "....................",
            "RR..RR..RR..RR..RR..",
            "RR..RR..RR..RR..RR..",
            "..OO..OO..OO..OO..OO",
            "..OO..OO..OO..OO..OO",
            "YY..YY..YY..YY..YY..",
            "YY..YY..YY..YY..YY..",
            "..GG..GG..GG..GG..GG",
            "..GG..GG..GG..GG..GG",
            "BB..BB..BB..BB..BB..",
            "BB..BB..BB..BB..BB..",
            "..PP..PP..PP..PP..PP",
            "..PP..PP..PP..PP..PP",
            "RR..RR..RR..RR..RR..",
            "RR..RR..RR..RR..RR..",
        }
    };

    const Level LEVEL_GATES = {
        L"Ворота", {
            "....................",
            "PPPPPPPPPPPPPPPPPPPP",
            "PPPPPPPPPPPPPPPPPPPP",
            "BBBB............BBBB",
            "BBBB............BBBB",
            "BBBB............BBBB",
            "GGGG............GGGG",
            "GGGG............GGGG",
            "GGGG............GGGG",
            "YYYY............YYYY",
            "YYYY............YYYY",
            "YYYY............YYYY",
            "OOOOOOOOOOOOOOOOOOOO",
            "OOOOOOOOOOOOOOOOOOOO",
            "RRRRRRRRRRRRRRRRRRRR",
            "RRRRRRRRRRRRRRRRRRRR",
        }
    };

    /* ===== MediumHard ===== */

    const Level LEVEL_FORTRESS = {
        L"Крепость", {
            "....................",
            "PPPPPPPPPPPPPPPPPPPP",
            "P..................P",
            "P.BBBBBBBBBBBBBBBB.P",
            "P.B..............B.P",
            "P.B.GGGGGGGGGGGG.B.P",
            "P.B.G..........G.B.P",
            "P.B.G.YYYYYYYY.G.B.P",
            "P.B.G.YYYYYYYY.G.B.P",
            "P.B.G..........G.B.P",
            "P.B.GGGGGGGGGGGG.B.P",
            "P.B..............B.P",
            "P.BBBBBBBBBBBBBBBB.P",
            "P..................P",
            "PPPPPPPPPPPPPPPPPPPP",
        }
    };

    const Level LEVEL_DIAGONALS = {
        L"Диагонали", {
            "....................",
            "RRRROOOOYYYYGGGGBBBB",
            "BRRRROOOOYYYYGGGGBBB",
            "BBRRRROOOOYYYYGGGGBB",
            "BBBRRRROOOOYYYYGGGGB",
            "BBBBRRRROOOOYYYYGGGG",
            "GBBBBRRRROOOOYYYYGGG",
            "GGBBBBRRRROOOOYYYYGG",
            "GGGBBBBRRRROOOOYYYYG",
            "GGGGBBBBRRRROOOOYYYY",
            "YGGGGBBBBRRRROOOOYYY",
            "YYGGGGBBBBRRRROOOOYY",
            "YYYGGGGBBBBRRRROOOOY",
            "YYYYGGGGBBBBRRRROOOO",
            "OYYYYGGGGBBBBRRRROOO",
            "OOYYYYGGGGBBBBRRRROO",
            "OOOYYYYGGGGBBBBRRRRO",
            "OOOOYYYYGGGGBBBBRRRR",
        }
    };

    const Level LEVEL_HONEYCOMB = {
        L"Соты", {
            "....................",
            "RRR..RRR..RRR..RRR..",
            "R..R.R..R.R..R.R..R.",
            "RRR..RRR..RRR..RRR..",
            "..OOO..OOO..OOO..OOO",
            ".O..O.O..O.O..O.O..O",
            "..OOO..OOO..OOO..OOO",
            "YYY..YYY..YYY..YYY..",
            "Y..Y.Y..Y.Y..Y.Y..Y.",
            "YYY..YYY..YYY..YYY..",
            "..GGG..GGG..GGG..GGG",
            ".G..G.G..G.G..G.G..G",
            "..GGG..GGG..GGG..GGG",
        }
    };

    /* ===== Hard ===== */

    const Level LEVEL_WALL = {
        L"Кирпичная стена", {
            "....................",
            "RRRRRRRRRRRRRRRRRRRR",
            "RR..RRRR..RRRR..RRRR",
            "RRRRRRRRRRRRRRRRRRRR",
            "OOOO..OOOO..OOOO..OO",
            "OOOOOOOOOOOOOOOOOOOO",
            "OO..OOOO..OOOO..OOOO",
            "YYYYYYYYYYYYYYYYYYYY",
            "YYYY..YYYY..YYYY..YY",
            "YYYYYYYYYYYYYYYYYYYY",
            "GG..GGGG..GGGG..GGGG",
            "GGGGGGGGGGGGGGGGGGGG",
            "GGGG..GGGG..GGGG..GG",
            "BBBBBBBBBBBBBBBBBBBB",
            "BB..BBBB..BBBB..BBBB",
            "BBBBBBBBBBBBBBBBBBBB",
            "PPPP..PPPP..PPPP..PP",
            "PPPPPPPPPPPPPPPPPPPP",
            "PP..PPPP..PPPP..PPPP",
        }
    };

    const Level LEVEL_MAZE = {
        L"Лабиринт", {
            "....................",
            "PPPPPPPPPPPPPPPPPPPP",
            "P..................P",
            "P.BBBBBBBBBBBBBBBB.P",
            "P.B..............B.P",
            "P.B.GGGGGGGGGGGG.B.P",
            "P.B.G..........G.B.P",
            "P.B.G.YYYYYYYY.G.B.P",
            "P.B.G.Y......Y.G.B.P",
            "P.B.G.Y.OOOO.Y.G.B.P",
            "P.B.G.Y.O..O.Y.G.B.P",
            "P.B.G.Y.OOOO.Y.G.B.P",
            "P.B.G.Y......Y.G.B.P",
            "P.B.G.YYYYYYYY.G.B.P",
            "P.B.G..........G.B.P",
            "P.B.GGGGGGGGGGGG.B.P",
            "P.B..............B.P",
            "P.BBBBBBBBBBBBBBBB.P",
            "P..................P",
            "PPPPPPPPPPPPPPPPPPPP",
        }
    };

    const Level LEVEL_TARGET = {
        L"Мишень", {
            "....................",
            "......RRRRRRRR......",
            "....RRRRRRRRRRRR....",
            "..RROOOOOOOOOOOORR..",
            ".RROOOOOOOOOOOOOORR.",
            "RROOYYYYYYYYYYYYOORR",
            "ROOYYYYYYYYYYYYYYOOR",
            "ROOYYGGGGGGGGGGYYOOR",
            "ROOYYGGGBBBBGGGYYOOR",
            "ROOYYGGGBBBBGGGYYOOR",
            "ROOYYGGGGGGGGGGYYOOR",
            "ROOYYYYYYYYYYYYYYOOR",
            "RROOYYYYYYYYYYYYOORR",
            ".RROOOOOOOOOOOOOORR.",
            "..RROOOOOOOOOOOORR..",
            "....RRRRRRRRRRRR....",
            "......RRRRRRRR......",
        }
    };

    const Level LEVEL_INVADERS = {
        L"Пришельцы", {
            "....................",
            "..RR............RR..",
            "....RR........RR....",
            "..RRRRRRRRRRRRRRRR..",
            ".RRR..RRRRRRRR..RRR.",
            "RRRRRRRRRRRRRRRRRRRR",
            "R.RRRRRRRRRRRRRRRR.R",
            "R.R..............R.R",
            "..YY............YY..",
            "....................",
            "..BB............BB..",
            "....BB........BB....",
            "..BBBBBBBBBBBBBBBB..",
            ".BBB..BBBBBBBB..BBB.",
            "BBBBBBBBBBBBBBBBBBBB",
            "B.BBBBBBBBBBBBBBBB.B",
            "B.B..............B.B",
            "..PP............PP..",
        }
    };

    const std::map<DifficultyLevel::Type, std::vector<Level>> LEVELS_BY_DIFFICULTY = {
        {DifficultyLevel::Type::Easy, {LEVEL_FIRST_STEPS, LEVEL_STAIRS, LEVEL_CLOUDS}},
        {DifficultyLevel::Type::EasyMedium, {LEVEL_PYRAMID, LEVEL_COMB, LEVEL_WAVE}},
        {DifficultyLevel::Type::Medium, {LEVEL_RAINBOW, LEVEL_CHECKERS, LEVEL_GATES}},
        {DifficultyLevel::Type::MediumHard, {LEVEL_FORTRESS, LEVEL_DIAGONALS, LEVEL_HONEYCOMB}},
        {DifficultyLevel::Type::Hard, {LEVEL_WALL, LEVEL_MAZE, LEVEL_TARGET, LEVEL_INVADERS}},
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
