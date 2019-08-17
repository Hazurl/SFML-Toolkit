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

    sftk::FancyText text = sftk::TextBuilder{ font_roboto }
    /*
        << txt::size(45)
        << "OO"sv
        << txt::size(12)
        << "OO"sv
    */
    
        << "Hel"sv
        << sf::Text::StrikeThrough
        << "lo "sv
        << sf::Color::Red
        << 'W'
        << sftk::txt::styles(sf::Text::Underlined, sf::Text::StrikeThrough)
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
        << txt::size(30)
        << sf::Color::Blue
        << txt::outline_thickness(0)
        << "H"sv
        << sf::Text::Regular
        << sftk::txt::styles(sf::Text::Underlined, sf::Text::StrikeThrough)
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
        << txt::spacing(1)
        << txt::line_spacing(2)
        << "ow with another font\n"sv
        << txt::line_spacing(1)
        << "ow with another font"sv
        ;

    sf::Text t("ow with another font", font_neo, 12);

    text.setPosition(0.5f * (800 - text.get_local_bounds().width), 0.5f * (600 - text.get_local_bounds().height));
    t.setPosition(0.5f * (800 - t.getLocalBounds().width), 350);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        window.draw(text);
        //window.draw(t);
        window.display();
    }

}