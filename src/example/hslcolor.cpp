#include <SFML/Graphics.hpp>

#include <sftk/hslcolor/HSLColor.hpp>
#include <sftk/print/Printer.hpp>

#include <iostream>

int main() {
    using namespace sftk;

    // Default constructor intialiaze to 0x00'00'00'FF, e.g. black
    HSLColor c0;

    // Similar constant as sf::Color
    HSLColor c1 = HSLColor::Green;

    // Construct from an integer
    HSLColor c2{ sf::Uint32{ 0xFF00FFFF }};

    // Construct from the hue, saturation and luminosity, alpha channel is the 4th parameter (defaulted to 0xFF)
    HSLColor c3{ 0xFF, 0x00, 0xFF };

    static_assert(std::is_same_v<RGBColor, sf::Color>, 
        "RGBColor is an alias to sf::Color, it's use to mirror the name 'HSLColor'");

    // `to_hsl` convert a RGBColor or sf::Color to a HSLColor
    HSLColor c4 = to_hsl(sf::Color::Cyan);
    // ... or using the red, green, blue and alpha channel (alpha defaulted to 0xFF)
    HSLColor c5 = to_hsl(0x00, 0xFF, 0xFF);

    // `to_rgb` convert a sf::Color or a RGBColor to a HSLColor
    sf::Color c6 = to_rgb(HSLColor::Cyan);

    // operator<< implemented
    std::cout << "c0= " << c0 << '\n';
    std::cout << "c1= " << c1 << '\n';
    std::cout << "c2= " << c2 << '\n';
    std::cout << "c3= " << c3 << '\n';
    std::cout << "c4= " << c4 << '\n';
    std::cout << "c5= " << c5 << '\n';
    std::cout << "c6= " << c6 << '\n';
}