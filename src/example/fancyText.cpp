#include <SFML/Graphics.hpp>

#include <sftk/fancyText/FancyText.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::Font font;
    if(!font.loadFromFile("/a/path/to/a/valid/font.ttf")) {
        return 1;
    }

    // You can change...
    sftk::FancyText text = sftk::TextBuilder{ font }
        << "Hello, "
    // the size...
        << sftk::txt::size(45)
    // the style...
        << sf::Text::Italic
        << "this"
        << sf::Text::Regular
    // the outline...
        << sftk::txt::outline_color(sf::Color{200, 100, 0})
        << sftk::txt::outline_thickness(3)
        << " is "
        << sftk::txt::outline_thickness(0)
        << sf::Text::Bold
    // the letter spacing...
        << sftk::txt::spacing(10)
        << "BIG!\n"
        << sftk::txt::spacing(1)
    // the line spacing...
        << sftk::txt::line_spacing(2)
        << 'A' << sf::Text::StrikeThrough << 'n' << sf::Text::Regular << "d "
        << sf::Text::Underlined
    // the color...
        << 'c' << sf::Color::Red
        << 'o' << sf::Color::Green
        << 'l' << sf::Color::White
        << 'o' << sf::Color::Blue
        << 'r' << sf::Color::Magenta
        << 'e' << sf::Color::Cyan
        << 'd' << sf::Color::Yellow
        << " !";

    // Put the text in the middle
    text.setPosition(0.5f * (window.getSize().x - text.get_local_bounds().width), 0.5f * (window.getSize().y - text.get_local_bounds().height));

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