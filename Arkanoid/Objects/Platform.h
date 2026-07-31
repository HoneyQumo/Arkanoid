#pragma once
#include "Objects/Collidable.h"
#include "Objects/GameObject.h"

namespace ArkanoidGame
{
    class Game;

    class Platform : public GameObject, public Collidable
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

        bool CheckCollision(Collidable& other) override;
        bool HasCollisionWith(const Collidable& other) const override;

        sf::FloatRect GetBounds() const override { return _sprite.getGlobalBounds(); }

    protected:
        void OnHit(Collidable& other) override;

    private:
        bool _sticky = true;
    };
}
