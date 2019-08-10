#include <SFML/Graphics.hpp>

#include <sftk/ressource/Ressource.hpp>
#include <sftk/fancyText/FancyText.hpp>
#include <sftk/print/Printer.hpp>

#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    using namespace sftk;

    sf::Font font_roboto;
    if (!font_roboto.loadFromFile("./assets/font/Roboto-Regular.ttf")) {
        return 1;
    }

    sf::Font font_neo;
    if (!font_neo.loadFromFile("./assets/font/neoletters.ttf")) {
        return 1;
    }

    using namespace std::string_view_literals;
    std::cout << "###############" << font_neo.getUnderlineThickness(30);
    std::cout << "###############" << font_roboto.getUnderlineThickness(30);

    sftk::FancyText text = sftk::TextBuilder{ font_neo }
        << (sf::Text::Style)(sf::Text::Underlined | sf::Text::StrikeThrough)
        << "O"sv
        << font_roboto
        << "O"sv
        << "O"sv
        << font_neo
        << "O"sv
        /*
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
        << "ame is"sv
        << txt::size(45)
        << '\n'
        << txt::size(30)
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
        << " and n"sv
        << txt::size(12)
        << "ow with another font\n"sv
        */;

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