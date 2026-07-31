#include <map>
#include "Data/Level.h"

namespace ArkanoidGame
{
    /* Сетка: 20 колонок, строка = 20 символов.
       Первая пустая строка задаёт отступ от верхнего края экрана.

       R G B P Y O — обычные кирпичи (одно попадание)
       A           — бронированный (три попадания, текстура меняется)
       X           — неразрушимый (в условие победы не входит)

       Правило: неразрушимые блоки никогда не отрезают обычные кирпичи
       от мяча — сплошные ряды X допустимы только у верхнего края,
       во всех остальных местах в них оставлены проходы. 
    */

    // TODO: вынести уровни в файлы, а не хранить тут

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
            ".......YYAAYY.......",
            ".......YYAAYY.......",
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
            ".........AA.........",
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
            ".....YYYYAAYYYY.....",
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
            "..AA..AA..AA..AA..AA",
            "RR..RR..RR..RR..RR..",
            "RR..RR..RR..RR..RR..",
        }
    };

    const Level LEVEL_GATES = {
        L"Ворота", {
            "....................",
            "PPPPPPPPPPPPPPPPPPPP",
            "PPPPPPPPPPPPPPPPPPPP",
            "BBBX............XBBB",
            "BBBX............XBBB",
            "BBBX............XBBB",
            "GGGX............XGGG",
            "GGGX............XGGG",
            "GGGX............XGGG",
            "YYYX............XYYY",
            "YYYX............XYYY",
            "YYYX............XYYY",
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
            "XXXXXXXXXXXXXXXXXXXX",
            "X..................X",
            "X.BBBBBBBBBBBBBBBB.X",
            "X.B..............B.X",
            "X.B.GGGGGGGGGGGG.B.X",
            "X.B.G..........G.B.X",
            "X.B.G.AAAAAAAA.G.B.X",
            "X.B.G.AAAAAAAA.G.B.X",
            "X.B.G..........G.B.X",
            "X.B.GGGGGGGGGGGG.B.X",
            "X.B..............B.X",
            "X.BBBBBBBBBBBBBBBB.X",
            "X..................X",
            "XXXXX..........XXXXX",
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
            ".G..A.G..A.G..A.G..A",
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
            "XX..XXXX..XXXX..XXXX",
            "YYYYYYYYYYYYYYYYYYYY",
            "YYYY..YYYY..YYYY..YY",
            "YYYYYYYYYYYYYYYYYYYY",
            "GGGG..AAAA..GGGG..GG",
            "GGGGGGGGGGGGGGGGGGGG",
            "GGGG..GGGG..GGGG..GG",
            "BBBBBBBBBBBBBBBBBBBB",
            "BB..BBBB..BBBB..BBBB",
            "BBBBBBBBBBBBBBBBBBBB",
            "PPPP..PPPP..PPPP..PP",
        }
    };

    const Level LEVEL_MAZE = {
        L"Лабиринт", {
            "....................",
            "XXXXXXXXXXXXXXXXXXXX",
            "X..................X",
            "X.BBBBBBBBBBBBBBBB.X",
            "X.B..............B.X",
            "X.B.GGGGGGGGGGGG.B.X",
            "X.B.G..........G.B.X",
            "X.B.G.YYYYYYYY.G.B.X",
            "X.B.G.Y......Y.G.B.X",
            "X.B.G.Y.AAAA.Y.G.B.X",
            "X.B.G.Y.A..A.Y.G.B.X",
            "X.B.G.Y.AAAA.Y.G.B.X",
            "X.B.G.Y......Y.G.B.X",
            "X.B.G.YYYYYYYY.G.B.X",
            "X.B.G..........G.B.X",
            "X.B.GGGGGGGGGGGG.B.X",
            "X.B..............B.X",
            "X.BBBBBBBBBBBBBBBB.X",
            "X..................X",
            "XXXXX..........XXXXX",
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
            "ROOYYGGGAAAAGGGYYOOR",
            "ROOYYGGGAAAAGGGYYOOR",
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
            "..XX............XX..",
            "....BB........BB....",
            "..BBBBBBBBBBBBBBBB..",
            ".BBB..BBBBBBBB..BBB.",
            "BBBBBBBBBBBBBBBBBBBB",
            "B.BBBBBBBBBBBBBBBB.B",
            "B.B..............B.B",
            "..AA............AA..",
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
