#pragma once
#include "GameObject.h"

namespace ArkanoidGame
{
    class Brick : public GameObject
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

        void Hit() { _isBreaking = true; }
        bool IsBreaking() const { return _isBreaking; }
        bool IsDestroyed() const override;

        static sf::IntRect GetBrickFrameRect(Color color, int frame);

        static Color GetColorByLevelSymbol(char symbol);

    private:
        static const std::map<Color, int> BRICK_COLOR_ROW;
        Color _color = Color::Red;
        bool _isBreaking = false;
        float _breakTimer = 0.f;
    };
}
