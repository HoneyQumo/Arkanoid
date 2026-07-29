#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    class Game;

    class GameObject
    {
    public:
        virtual ~GameObject() = default;

        virtual void Init(Game& game) = 0;

        virtual void Update(Game& game, float dt) = 0;
        virtual void Draw(sf::RenderWindow& window) const;

        virtual bool IsDestroyed() const { return false; }

        sf::Sprite& GetSprite() { return _sprite; }
        const sf::Sprite& GetSprite() const { return _sprite; }

    protected:
        sf::Sprite _sprite;
    };
}
