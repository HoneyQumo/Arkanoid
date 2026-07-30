#pragma once
#include <map>
#include "Collidable.h"
#include "GameObject.h"

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

        enum class Kind
        {
            Colored = 0,
            Armored,
            Unbreakable,
        };

        Brick(Kind kind, Color color, sf::Vector2f position);

        void Init(Game& game) override;
        void Update(Game& game, float dt) override;

        bool IsBreaking() const { return _isBreaking; }
        bool IsUnbreakable() const { return _kind == Kind::Unbreakable; }
        bool IsDestroyed() const override;

        static Kind GetKindByLevelSymbol(char symbol);
        static Color GetColorByLevelSymbol(char symbol);

        bool CheckCollision(std::shared_ptr<Collidable> collidable) override;
        bool HasCollisionWith(std::shared_ptr<Collidable> collidable) const override;

        sf::FloatRect GetBounds() const override { return _sprite.getGlobalBounds(); }

    protected:
        void OnHit() override;

    private:
        static sf::IntRect GetBrickFrameRect(Color color, int frame);

        static const std::map<Color, int> BRICK_COLOR_ROW;

        Kind _kind = Kind::Colored;
        Color _color = Color::Red;
        unsigned _hitPoints = 1;
        bool _isBreaking = false;
        float _breakTimer = 0.f;

        sf::IntRect GetIdleRect() const;
    };
}
