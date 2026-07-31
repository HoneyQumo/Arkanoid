#include "Core/Settings.h"

namespace ArkanoidGame
{
    bool& Settings::GetState(const Type& type)
    {
        return _states[type];
    }
}
