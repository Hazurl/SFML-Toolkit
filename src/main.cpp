#include <SFML/Graphics.hpp>

#include <sftk/HSLColor/HSLColor.hpp>

#include <iostream>

int main() {
    using namespace sftk;

    HSLColor c0;
    HSLColor c1 = HSLColor::Cyan;
    HSLColor c2{ sf::Uint32{ 0xFF00FFFF }};
    HSLColor c3{ 0xFF, 0x00, 0xFF };
    HSLColor c4 = to_hsl(sf::Color::Cyan);

    std::cout << "c0= " << c0 << '\n';
    std::cout << "c1= " << c1 << '\n';
    std::cout << "c2= " << c2 << '\n';
    std::cout << "c3= " << c3 << '\n';
    std::cout << "c4= " << c4 << '\n';

}