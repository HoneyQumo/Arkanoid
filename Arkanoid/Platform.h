#pragma once
#include "GameObject.h"

namespace ArkanoidGame
{
    class Game;
    class Ball;

    class Platform : public GameObject
    {
    public:
        void Init(Game& game) override;
        void Update(Game& game, float dt) override;

        void Control(Ball& ball, float dt);

        void SetSticky(const bool& value);
        bool GetSticky() const;

    private:
        bool _sticky = true;
    };
}
