#include <SFML/Graphics.hpp>

#include <sftk/ressource/Ressource.hpp>
#include <sftk/fancyText/FancyText.hpp>
#include <sftk/print/Printer.hpp>

#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    using namespace sftk;

    sf::Font font_roboto;
    if (!font_roboto.loadFromFile("../../../Downloads/Roboto/Roboto-Regular.ttf")) {
        return 1;
    }

    sf::Font font_neo;
    if (!font_roboto.loadFromFile("../multi-pong/assets/neoletters.ttf")) {
        return 1;
    }

    using namespace std::string_view_literals;

    sftk::FancyText text = sftk::TextBuilder{ font_roboto }
        << "Hel"sv
        << sf::Text::StrikeThrough
        << "lo "sv
        << sf::Color::Red
        << 'W'
        << (sf::Text::Style)(sf::Text::Underlined | sf::Text::StrikeThrough)
        << "o"sv
        << sf::Text::Underlined
        << 'r'
        << sf::Text::Bold
        << "ld"sv
        << (sf::Text::Style)(sf::Text::Italic | sf::Text::Bold)
        << "! My n"sv
        << txt::outline_color(sf::Color::White)
        << txt::outline_thickness(2)
        << "ame is\n"sv
        << sf::Color::Blue
        << txt::outline_thickness(0)
        << "H"sv
        << sf::Text::Regular
        << (sf::Text::Style)(sf::Text::Underlined | sf::Text::StrikeThrough)
        << 'a'
        << txt::size(45)
        << txt::spacing(2)
        << "zu"sv
        << sf::Text::Regular
        << "rl"sv
        << font_neo
        << " and now with another font\n"sv;

    text.setPosition(0.5f * (800 - text.bounds.width), 200);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        window.draw(text);
        window.display();
    }

}