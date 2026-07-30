#pragma once
#include "GameObject.h"

namespace ArkanoidGame
{
    class Game;

    class Platform : public GameObject
    {
    public:
        void Init(Game& game) override;
        void Update(Game& game, float dt) override;

        /* Только перемещение и курсор: запуск мяча живёт в GameStatePlaying,
           потому что мячей может быть несколько */
        void Control(float dt);

        void SetWidth(float width);

        void SetSticky(const bool& value);
        bool GetSticky() const;

    private:
        bool _sticky = true;
    };
}
