#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

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

    constexpr sf::Uint32 to_integer() const noexcept {
        return static_cast<sf::Uint32>(h) << 24 | static_cast<sf::Uint32>(s) << 16 | static_cast<sf::Uint32>(l) << 8 | static_cast<sf::Uint32>(a) << 0;
    }

    sf::Uint8 h{ 0 }; 
    sf::Uint8 s{ 0 };
    sf::Uint8 l{ 0 };
    sf::Uint8 a{ 255 };

    static HSLColor const Black;
    static HSLColor const White;
    static HSLColor const Red;
    static HSLColor const Green;
    static HSLColor const Blue;
    static HSLColor const Yellow;
    static HSLColor const Cyan;
    static HSLColor const Magenta;
    static HSLColor const Transparent;

};




std::ostream& operator<<(std::ostream& os, HSLColor c);




RGBColor to_rgb(sf::Uint8 hue, sf::Uint8 saturation, sf::Uint8 luminosity, sf::Uint8 alpha = 255) noexcept;

constexpr HSLColor to_hsl(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha = 255) noexcept;

inline RGBColor to_rgb(HSLColor hsl) noexcept {
    return to_rgb(hsl.h, hsl.s, hsl.l, hsl.a);
}

inline HSLColor to_hsl(RGBColor rgb) noexcept {
    return to_hsl(rgb.r, rgb.g, rgb.b, rgb.a);
}




constexpr HSLColor to_hsl(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha) noexcept {
    float r = static_cast<float>(red) / 255.0f;
    float g = static_cast<float>(green) / 255.0f;
    float b = static_cast<float>(blue) / 255.0f;

    float* c_max = &b;
    if (r >= g && r >= b) {
        c_max = &r;
    }
    else if (g >= r && g >= b) {
        c_max = &g;
    }

    float c_min = std::min(r, std::min(g, b));
    float diff = *c_max - c_min;

    float h = 0;
    if (diff != 0) {
        if(c_max == &r) {
            h = 60.f * std::fmod((g - b) / diff, 6.f); 
        } 
        else if (c_max == &g) {
            h = 60.f * ((b - r) / diff + 2.f); 
        }
        else {
            h = 60.f * ((r - g) / diff + 4.f); 
        }
    }

    float l = (*c_max + c_min) / 2.f;
    float s = diff == 0 ? 0.f : (diff / (1 - std::abs(2 * l - 1)));

    return HSLColor{
        static_cast<sf::Uint8>(h / 360.f * 255.f), static_cast<sf::Uint8>(s * 255.f), static_cast<sf::Uint8>(l * 255.f), alpha
    };
}

}