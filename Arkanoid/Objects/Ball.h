#pragma once
#include "SFML/Graphics.hpp"
#include "Objects/Collidable.h"
#include "Objects/Platform.h"

namespace ArkanoidGame
{
    class Ball : public GameObject, public Collidable
    {
    public:
        void Init(Game& game) override;
        void Launch();
        void Update(Game& game, float dt) override;

        void AttachToPlatform(const Platform& platform);

        bool IsFallen() const;

        bool IsDestroyed() const override { return _isFallen; }

        void SetAttached(const bool& value);
        bool GetAttached() const;

        void SetVelocity(sf::Vector2f value);
        sf::Vector2f& GetVelocity();

        void SetSpeed(float value) { _speed = value; }
        float GetSpeed() const { return _speed; }

        void BounceOffPlatform(const Platform& platform);

        void BounceOffWall();

        void BounceOffRect(const sf::FloatRect& rectBounds);

        bool HasCollisionWith(const Collidable& other) const override;

        sf::FloatRect GetBounds() const override { return _sprite.getGlobalBounds(); }

    protected:
        void OnHit(Collidable& other) override;

    private:
        void NormalizeVelocity(float speed);

        sf::Vector2f _velocity{0.f, 0.f};
        float _speed = 0.f;
        bool _attached = true;
        bool _isFallen = false;
    };
}
