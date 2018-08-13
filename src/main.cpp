#include <SFML/Graphics.hpp>

#include <sftk/print/Printer.hpp>

#include <iostream>

int main() {

    using sftk::operator<<;

    std::cout << sf::Vector2f(42.42f, 1337) << '\n';
    std::cout << sf::Vector2i(42, -1337) << '\n';
    std::cout << sf::Vector2u(42, 1337) << '\n';

    std::cout << [] () { auto s = sf::CircleShape(12); s.setPosition({10, -20}); return s; }() << '\n';

}