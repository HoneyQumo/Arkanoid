#include "Objects/GameObject.h"

namespace ArkanoidGame
{
    void GameObject::Draw(sf::RenderWindow& window) const
    {
        window.draw(_sprite);
    }
}
