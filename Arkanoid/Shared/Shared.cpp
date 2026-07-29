#include "Shared.h"

namespace ArkanoidGame
{
    void InitText(
        sf::Text& node,
        const sf::String& text,
        const sf::Font& font,
        const unsigned textSize,
        const sf::Color color,
        const sf::Vector2f origin
    )
    {
        node.setString(text);
        node.setFont(font);
        node.setCharacterSize(textSize);
        node.setFillColor(color);
        node.setOrigin(GetTextOrigin(node, origin));
    }

    void InitHintText(sf::Text& node, const sf::String& text, const sf::Font& font)
    {
        InitText(node, text, font, TEXT_HINT, HINT_COLOR);
        node.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - HINT_OFFSET_BOTTOM);
    }
}
