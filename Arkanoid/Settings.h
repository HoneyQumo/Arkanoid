#pragma once
#include <map>

namespace ArkanoidGame
{
    class Settings
    {
    public:
        enum class Type
        {
            Sound = 0,
            Music,
            ResetLeaderboard,
        };

        bool& GetState(const Type& type);
        
    private:
        std::map<Type, bool> _states = {
            {Type::Sound, true},
            {Type::Music, true},
        };
    };
}
