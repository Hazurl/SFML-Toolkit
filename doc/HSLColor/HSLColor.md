# HSL Color

This system provides a similar class to `sf::Color` but using the hue/saturation/luminosity representation. It can be use, for example, to interpolate more naturally between 2 colors.

**Summary**
- [HSL Color](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/HSLColor/HSLColor.md#hsl-color)
- [Conversion](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/HSLColor/HSLColor.md#conversion)
- [Note on constexpr](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/HSLColor/HSLColor.md#note-on-constexpr)
- [Example](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/HSLColor/HSLColor.md#example)

## HSL Color

`sftk::HSLColor` is very similar to `sf::Color`. The properties can be accessed through the members `h` (hue), `s` (saturation), `l` (luminosity) and `a` (alpha). 

### Constructors

The default-constructor `sftk::HSLColor::HSLColor()` initialize the color to opaque black.\
`sftk::HSLColor::HSLColor(sf::Uint8 hue, sf::Uint8 saturation, sf::Uint8 luminosity, sf::Uint8 alpha = 255)` construct from the HSL and alpha properties.\
And `sftk::HSLColor::HSLColor(sf::Uint32 color)` construct the color from it's 32-bit representation: `hue << 24 | sat << 16 | lum << 8 | alpha`.

### to_integer

`sftk::HSLColor::to_integer` is the equivalent of `sf::Color::toInteger`, it returns the 32-bit HSL(A) representation of the color.

### Constants

`sftk::HSLColor::Black`, `White`, `Red`, `Green`, `Blue`, `Yellow`, `Cyan`, `Magenta` and `Transparent` are the HSL representation of `sf::Color::Black`, `White`, `Red`, `Green`, `Blue`, `Yellow`, `Cyan`, `Magenta` and `Transparent`.

### operator<<

`operator<<(std::ostream&, sftk::HSLColor)` is implemented.

## Conversion

`sftk::to_rgb(sf::Uint8 hue, sf::Uint8 saturation, sf::Uint8 luminosity, sf::Uint8 alpha = 255)` and `sftk::to_rgb(sftk::HSLColor)` will convert the HSL representation to the RGB representation (`sf::Color`).
`sftk::to_hsl(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha = 255)` and `sftk::to_hsl(sf::Color)` will convert the RGB representation to the HSL representation (`sftk::HSLColor`).

## Note on constexpr

The `sftk::HSLColor` is entirely constexpr, except the constants as they are in the scope of the class. `to_hsl(r, g, b)` can be used as a replacement. Also note that `sf::Color` isn't constexpr, so `to_hsl(sf::Color)` and both overloads of `to_rgb` are not constexpr.

## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/hslcolor.cpp)

```cpp
#include <SFML/Graphics.hpp>

#include <sftk/HSLColor/HSLColor.hpp>
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
}```