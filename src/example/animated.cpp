#include <SFML/Graphics.hpp>

#include <sftk/animated/Animated.hpp>

#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    using namespace sftk;

    /*
        Click in the windows to animate the balls towards your mouse
        One of them use a linear animation 
        and the other follows a bezier curve with the center as the only anchor
    */

    float const radius = 10;

    sf::CircleShape linear_circle(20);
    linear_circle.setOrigin(radius, radius);
    linear_circle.setFillColor(sf::Color{ 0x7A, 0x77, 0xD9, 123 });

    sf::CircleShape bezier_circle(20);
    bezier_circle.setOrigin(radius, radius);
    bezier_circle.setFillColor(sf::Color{ 0xF2, 0x50, 0x5D, 123 });

    sf::Vector2f const initial_position{ 400, 300 };
    Animated linear_position(interpolation::linear<sf::Vector2f>, initial_position);
    Animated bezier_position(interpolation::Bezier<sf::Vector2f>{{ initial_position }}, sf::Vector2f{});
    linear_circle.setPosition(linear_position.current());
    bezier_circle.setPosition(bezier_position.current());

    sf::Clock clock;

    // Controls
    std::cout << "Click in the windows to mvoe the balls to the mouse\n";
    std::cout << "The blue ball move linearly and the red ball along a bezier curve with an anchor in the center of the window\n";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f target{ static_cast<float>(event.mouseButton.x) - radius, static_cast<float>(event.mouseButton.y) - radius };

                linear_position.animate(target, 1);
                bezier_position.animate(target, 1, {{ initial_position }});
            }
        }

        auto dt = clock.restart().asSeconds();
        linear_position.update(dt);
        bezier_position.update(dt);
        linear_circle.setPosition(linear_position);
        bezier_circle.setPosition(bezier_position);

        window.clear();

        window.draw(linear_circle);
        window.draw(bezier_circle);

        window.display();
    }

}