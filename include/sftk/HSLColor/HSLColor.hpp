#pragma once

#include <SFML/Graphics.hpp>

namespace sftk {

using RGBColor = sf::Color;

struct HSLColor {

    constexpr HSLColor() noexcept = default;

    constexpr HSLColor(sf::Uint8 hue, sf::Uint8 saturation, sf::Uint8 luminosity, sf::Uint8 alpha = 255) noexcept
    :   h{ hue }
    ,   s{ saturation }
    ,   l{ luminosity }
    ,   a{ alpha }
    {}

    constexpr explicit HSLColor(sf::Uint32 color) noexcept : HSLColor(color >> 24 & 0xFF, color >> 16 & 0xFF, color >> 8 & 0xFF, color >> 0 & 0xFF) {}

    constexpr sf::Uint32 toInteger() const noexcept {
        return static_cast<sf::Uint32>(h) << 24 | static_cast<sf::Uint32>(s) << 16 | static_cast<sf::Uint32>(l) << 8 | static_cast<sf::Uint32>(a) << 0;
    }

    static constexpr HSLColor Black;
    static constexpr HSLColor White;
    static constexpr HSLColor Red;
    static constexpr HSLColor Green;
    static constexpr HSLColor Blue;
    static constexpr HSLColor Yellow;
    static constexpr HSLColor Magenta;
    static constexpr HSLColor Cyan;
    static constexpr HSLColor Transparent;

    sf::Uint8 h; 
    sf::Uint8 s;
    sf::Uint8 l;
    sf::Uint8 a;
};

constexpr sf::Color to_rgb(HSLColor hsl) noexcept {
    return {};
}

constexpr HSLColor to_hsl(sf::Color hsl) noexcept {
    return {};
}

}