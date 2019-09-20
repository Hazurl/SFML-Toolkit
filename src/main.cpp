#include <SFML/Graphics.hpp>

#include <sftk/ressource/Ressource.hpp>
#include <sftk/fancyText/FancyText.hpp>
#include <sftk/print/Printer.hpp>
#include <sftk/animated/Animated.hpp>

#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    using namespace sftk;

    sf::Font font_neo;
    if (!font_neo.loadFromFile("./assets/font/neoletters.ttf")) {
        return 1;
    }

    using namespace std::string_view_literals;

    sf::CircleShape circle(20);
    circle.setOrigin(10, 10);

    float const initial_height{ 550 };
    Animated<float, interpolation::Bezier<float>> height(initial_height);
    circle.setPosition(400, height.current());

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                height = static_cast<float>(event.mouseButton.y);
                circle.setPosition(static_cast<float>(event.mouseButton.x), height.current());
                height.animate(initial_height, 2, { static_cast<float>(event.mouseButton.y), initial_height });
            }/*
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                std::cout << "Animate !\n";
            } */
        }

        auto dt = clock.restart().asSeconds();
        height.update(dt);
        circle.setPosition(circle.getPosition().x, height.current());

        window.clear();

        window.draw(circle);

        window.display();
    }

}