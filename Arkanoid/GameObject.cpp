#include "GameObject.h"

namespace ArkanoidGame
{
    void GameObject::Draw(sf::RenderWindow& window) const
    {
        window.draw(_sprite);
    }

    sf::Sprite& GameObject::GetSprite()
    {
        return _sprite;
    }
}
