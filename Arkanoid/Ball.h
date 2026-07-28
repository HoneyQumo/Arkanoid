#pragma once
#include "SFML/Graphics.hpp"
#include "Platform.h"

namespace ArkanoidGame
{
    class Ball : public GameObject
    {
    public:
        void Init(Game& game) override;
        void Launch();
        void Update(Game& game, float dt) override;

        void AttachToPlatform(const Platform& platform);

        void SetAttached(const bool& value);
        bool GetAttached() const;

        void SetVelocity(sf::Vector2f value);
        sf::Vector2f& GetVelocity();

        void BounceOffPlatform(Platform& platform, float speed);

        void BounceOffWall(float speed);

        void NormalizeVelocity(float speed);

    private:
        sf::Vector2f _velocity{0.f, 0.f};
        bool _attached = true;
    };
}
