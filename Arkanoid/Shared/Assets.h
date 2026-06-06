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
                        menuToggleBuffer,
                        menuSelectBuffer;

        sf::Sound music,
                  death,
                  menuToggle,
                  menuSelect;

        sf::Texture atlas;
        
        void Init();
    };
}
