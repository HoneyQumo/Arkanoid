#include "Assets.h"
#include <cassert>
#include "Constants.h"

namespace ArkanoidGame
{
    void Assets::Init()
    {
        /* Fonts */
        assert(font.loadFromFile(RESOURCES_FONTS + "\\pixel_font-7.ttf"));

        /* Graphics */
        assert(atlas.loadFromFile(RESOURCES_GRAPHICS + "\\spritesheet-atlas.png"));

        const bool isHeartLoaded = heart.loadFromFile(RESOURCES_GRAPHICS + "\\heart.png");
        assert(isHeartLoaded);

        const bool isPowerupsLoaded = powerups.loadFromFile(RESOURCES_GRAPHICS + "\\powerups.png");
        assert(isPowerupsLoaded);

        /* Sounds */
        assert(musicBuffer.loadFromFile(RESOURCES_AUDIO + "\\music.wav"));
        music.setBuffer(musicBuffer);
        music.setVolume(MUSIC_INITIAL_VOLUME);

        assert(deathBuffer.loadFromFile(RESOURCES_AUDIO + "\\death.wav"));
        death.setBuffer(deathBuffer);
        death.setVolume(SOUNDS_INITIAL_VOLUME);

        const bool isDestroyLoaded = destroyBuffer.loadFromFile(RESOURCES_AUDIO + "\\destroy.wav");
        assert(isDestroyLoaded);
        destroy.setBuffer(destroyBuffer);
        destroy.setVolume(SOUNDS_INITIAL_VOLUME);

        // assert(eatBuffer.loadFromFile(RESOURCES_AUDIO + "\\eat.wav"));
        // eat.setBuffer(eatBuffer);
        // eat.setVolume(SOUNDS_INITIAL_VOLUME);

        assert(menuToggleBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-toggle.wav"));
        menuToggle.setBuffer(menuToggleBuffer);
        menuToggle.setVolume(SOUNDS_INITIAL_VOLUME);

        assert(menuSelectBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-select.wav"));
        menuSelect.setBuffer(menuSelectBuffer);
        menuSelect.setVolume(SOUNDS_INITIAL_VOLUME);
    }
}
