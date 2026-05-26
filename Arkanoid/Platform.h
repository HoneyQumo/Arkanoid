#pragma once
#include "GameObject.h"

namespace ArkanoidGame
{
    class Game;
    class Ball;

    class Platform : public GameObject
    {
    public:
        void Init(Game& game);
        void Update(Ball& ball, float dt);

        void Control(Ball& ball, float dt);

        void SetSticky(const bool& value);
        bool GetSticky() const;

    private:
        bool _sticky = true;
    };
}
