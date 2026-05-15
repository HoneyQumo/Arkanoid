#pragma once
#include "SFML/Graphics.hpp"
#include "Shared/Constants.h"
#include "Shared/Math.h"

namespace ArkanoidGame
{
    struct Apple
    {
        sf::Sprite sprite;
    };

    Apple CreateApple(const sf::Texture& texture, const sf::Vector2f& position);
    void DrawApples(sf::RenderWindow& window, const std::vector<Apple>& apples);

    class Game;
    void SpawnApple(Game& game);
}
