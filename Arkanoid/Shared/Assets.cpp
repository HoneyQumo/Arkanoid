#include "Assets.h"
#include <cassert>
#include <string>
#include "Constants.h"

namespace ArkanoidGame
{
    namespace
    {
        template <typename TResource>
        void LoadOrFail(TResource& resource, const std::string& path)
        {
            const bool isLoaded = resource.loadFromFile(path);

            assert(isLoaded);
            (void)isLoaded;
        }

        void LoadSound(sf::SoundBuffer& buffer, sf::Sound& sound, const std::string& path, const float volume)
        {
            LoadOrFail(buffer, path);

            sound.setBuffer(buffer);
            sound.setVolume(volume);
        }
    }

    void Assets::Init()
    {
        /* Fonts */
        LoadOrFail(font, RESOURCES_FONTS + "\\pixel_font-7.ttf");

        /* Graphics */
        LoadOrFail(atlas, RESOURCES_GRAPHICS + "\\spritesheet-atlas.png");
        LoadOrFail(heart, RESOURCES_GRAPHICS + "\\heart.png");
        LoadOrFail(powerups, RESOURCES_GRAPHICS + "\\powerups.png");

        /* Sounds */
        LoadSound(musicBuffer, music, RESOURCES_AUDIO + "\\music.wav", MUSIC_INITIAL_VOLUME);
        LoadSound(deathBuffer, death, RESOURCES_AUDIO + "\\death.wav", SOUNDS_INITIAL_VOLUME);
        LoadSound(destroyBuffer, destroy, RESOURCES_AUDIO + "\\destroy.wav", SOUNDS_INITIAL_VOLUME);
        LoadSound(menuToggleBuffer, menuToggle, RESOURCES_AUDIO + "\\menu-toggle.wav", SOUNDS_INITIAL_VOLUME);
        LoadSound(menuSelectBuffer, menuSelect, RESOURCES_AUDIO + "\\menu-select.wav", SOUNDS_INITIAL_VOLUME);
    }
}
