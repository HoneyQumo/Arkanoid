#pragma once
#include <string>
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
    /* Paths */
    const std::string RESOURCES_PATH = "Resources/";
    const std::string RESOURCES_AUDIO = RESOURCES_PATH + "Audio";
    const std::string RESOURCES_FONTS = RESOURCES_PATH + "Fonts";
    const std::string RESOURCES_GRAPHICS = RESOURCES_PATH + "Graphics";

    const std::string LEADERBOARD_FILE_PATH = "leaderboard.txt";

    /* Video */
    constexpr unsigned SCREEN_WIDTH = 1000;
    constexpr unsigned SCREEN_HEIGHT = 1000;
    constexpr float TOTAL_PIXELS = (SCREEN_WIDTH + SCREEN_HEIGHT) / 2.f;
    constexpr float OFFSET_TOP_WINDOW_10_PERCENT = (SCREEN_HEIGHT / 100.f) * 10.f;
    constexpr float OFFSET_TOP_WINDOW_20_PERCENT = (SCREEN_HEIGHT / 100.f) * 20.f;

    /* Audio */
    constexpr float MUSIC_INITIAL_VOLUME = 15.f;
    constexpr float SOUNDS_INITIAL_VOLUME = 50.f;

    /* General */
    const std::string GAME_NAME = "Arkanoid";

    /* Player */
    constexpr unsigned PLAYER_INITIAL_LIVES = 3;

    /* HUD */
    constexpr float HUD_Y_POSITION = SCREEN_HEIGHT - 68.f;
    constexpr float HUD_MARGIN_SIDE = 20.f;
    constexpr float HEART_SIZE = 26.f;
    constexpr float HEART_GAP = 6.f;

    /* Platform */
    constexpr float PLATFORM_WIDTH = SCREEN_WIDTH * 0.2f;
    constexpr float PLATFORM_HEIGHT = SCREEN_HEIGHT * 0.02f;
    constexpr float PLATFORM_SPEED = TOTAL_PIXELS / 1.5f;
    constexpr float PLATFORM_Y_POSITION = SCREEN_HEIGHT - 100.f;

    /* Ball */
    constexpr float BALL_SIZE = 20.f;

    /* Brick */
    constexpr int BRICK_ATLAS_LEFT = 32;
    constexpr int BRICK_ATLAS_TOP = 176;
    constexpr int BRICK_FRAME_COUNT = 11;
    constexpr int BRICK_FRAME_WIDTH = 32;
    constexpr int BRICK_FRAME_HEIGHT = 16;

    constexpr float BRICK_WIDTH = SCREEN_WIDTH * 0.05f;
    constexpr float BRICK_HEIGHT = BRICK_WIDTH / 2.f;

    constexpr float BRICK_DESTROY_FRAME_DURATION = 0.04f;

    /* Text */
    constexpr unsigned TEXT_HEADING_1 = 60;
    constexpr unsigned TEXT_HEADING_2 = 50;
    constexpr unsigned TEXT_HEADING_3 = 40;
    constexpr unsigned TEXT_MENU_ITEM = 30;
    constexpr unsigned TEXT_HINT = 20;

    constexpr float HINT_OFFSET_BOTTOM = 40.f;
    const auto HINT_COLOR = sf::Color(150, 150, 150);
    const sf::String INPUT_PLACEHOLDER = L"Введите имя (XYZ)";
}
