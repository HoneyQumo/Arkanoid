#pragma once
#include <map>
#include "Objects/Collidable.h"
#include "Objects/GameObject.h"

namespace ArkanoidGame
{
    class Brick : public GameObject, public Collidable
    {
    public:
        enum class Color
        {
            Red = 0,
            Green,
            Blue,
            Purple,
            Yellow,
            Orange,
        };

        Brick(Color color, sf::Vector2f position);

        void Init(Game& game) override;
        void Update(Game& game, float dt) override;

        bool IsBreaking() const { return _isBreaking; }
        virtual bool IsUnbreakable() const { return false; }
        bool IsDestroyed() const override;

        static Color GetColorByLevelSymbol(char symbol);

        bool CheckCollision(Collidable& other) override;
        bool HasCollisionWith(const Collidable& other) const override;

        sf::FloatRect GetBounds() const override { return _sprite.getGlobalBounds(); }

    protected:
        void OnHit(Collidable& other) override;

        virtual sf::IntRect GetIdleRect() const;

        static sf::IntRect GetBrickFrameRect(Color color, int frame);

    private:
        static const std::map<Color, int> BRICK_COLOR_ROW;

        Color _color = Color::Red;
        bool _isBreaking = false;
        float _breakTimer = 0.f;
    };
}
