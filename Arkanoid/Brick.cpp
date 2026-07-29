#include "Brick.h"
#include "Application.h"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    void Brick::Init(Game& game)
    {
        _sprite = sf::Sprite(game.assets.atlas);
        _sprite.setTextureRect(GetBrickFrameRect(_color, 0));
        SetSpriteSize(_sprite, BRICK_WIDTH, BRICK_HEIGHT);
        SetSpriteOrigin(_sprite, {0.5f, 0.5f});
        // SetSpriteOrigin(_sprite, {0.f, 0.f});
        _sprite.setPosition(SCREEN_WIDTH / 2.f, BRICK_HEIGHT / 2.f);
    }

    void Brick::Update(Game& game, float dt)
    {
        if (!_isBreaking) return;

        _breakTimer += dt;
        const int frame = static_cast<int>(_breakTimer / BRICK_DESTROY_FRAME_DURATION);

        if (frame < BRICK_FRAME_COUNT)
        {
            _sprite.setTextureRect(GetBrickFrameRect(_color, frame));
        }
    }

    bool Brick::IsDestroyed() const
    {
        return _isBreaking && (_breakTimer / BRICK_DESTROY_FRAME_DURATION) >= BRICK_FRAME_COUNT;
    }

    sf::IntRect Brick::GetBrickFrameRect(const Color color, const int frame)
    {
        return {
            BRICK_ATLAS_LEFT + frame * BRICK_FRAME_WIDTH,
            BRICK_ATLAS_TOP + BRICK_COLOR_ROW.at(color) * BRICK_FRAME_HEIGHT,
            BRICK_FRAME_WIDTH,
            BRICK_FRAME_HEIGHT,
        };
    }

    const std::map<Brick::Color, int> Brick::BRICK_COLOR_ROW = {
        {Color::Red, 0},
        {Color::Green, 1},
        {Color::Blue, 2},
        {Color::Purple, 3},
        {Color::Yellow, 4},
        {Color::Orange, 5},
    };
}
