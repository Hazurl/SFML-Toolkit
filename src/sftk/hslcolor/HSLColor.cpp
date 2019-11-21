#include <sftk/hslcolor/HSLColor.hpp>

namespace sftk {

HSLColor const HSLColor::Black      {   0,   0,   0, 255 };
HSLColor const HSLColor::White      {   0,   0, 255, 255 };
HSLColor const HSLColor::Red        {   0, 255, 127, 255 };
HSLColor const HSLColor::Green      {  85, 255, 127, 255 };
HSLColor const HSLColor::Blue       { 170, 255, 127, 255 };
HSLColor const HSLColor::Yellow     {  42, 255, 127, 255 };
HSLColor const HSLColor::Cyan       { 127, 255, 127, 255 };
HSLColor const HSLColor::Magenta    { 212, 255, 127, 255 };
HSLColor const HSLColor::Transparent{   0,   0,   0,   0 };

sf::Color to_rgb(sf::Uint8 hue, sf::Uint8 saturation, sf::Uint8 luminosity, sf::Uint8 alpha) noexcept {
    float c = (1.f - std::abs(2.f * static_cast<float>(luminosity) - 1.f)) * static_cast<float>(saturation);
    float x = c * (1.f - std::abs(std::fmod(static_cast<float>(hue) / 42.5f, 2.f) - 1.f));
    float m = static_cast<float>(luminosity) - c/2.f;

    float r = 0, g = 0, b = 0;
    if (hue < 42.5f) {
        r = c;
        g = x;
    }
    else if (hue < 85.f) {
        r = x;
        g = c;
    }
    else if (hue < 127.5f) {
        g = c;
        b = x;
    }
    else if (hue < 170.f) {
        g = x;
        b = c;
    }
    else if (hue < 212.5f) {
        r = x;
        b = c;
    }
    else {
        r = c;
        b = x;
    }

    return sf::Color(
        static_cast<sf::Uint8>((r + m) * 255.f),
        static_cast<sf::Uint8>((g + m) * 255.f),
        static_cast<sf::Uint8>((b + m) * 255.f),
        alpha
    );
}

std::ostream& operator<<(std::ostream& os, HSLColor c) {
    return os << "HSLColor {" << static_cast<unsigned>(c.h) << ", " << static_cast<unsigned>(c.s) << ", " << static_cast<unsigned>(c.l) << ", " << static_cast<unsigned>(c.a) << "}";
}

}