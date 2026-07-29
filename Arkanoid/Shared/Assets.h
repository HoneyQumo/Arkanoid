#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace ArkanoidGame
{
    class Assets
    {
    public:
        sf::Font font;

        sf::SoundBuffer musicBuffer,
                        deathBuffer,
                        destroyBuffer,
                        menuToggleBuffer,
                        menuSelectBuffer;

        sf::Sound music,
                  death,
                  destroy,
                  menuToggle,
                  menuSelect;

        sf::Texture atlas;
        sf::Texture heart;

        void Init();
    };
}
