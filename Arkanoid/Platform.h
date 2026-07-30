#pragma once
#include "Collidable.h"
#include "GameObject.h"

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

        bool CheckCollision(std::shared_ptr<Collidable> collidable) override;
        bool HasCollisionWith(std::shared_ptr<Collidable> collidable) const override;

        sf::FloatRect GetBounds() const override { return _sprite.getGlobalBounds(); }

    protected:
        void OnHit() override;

    private:
        bool _sticky = true;
    };
}
