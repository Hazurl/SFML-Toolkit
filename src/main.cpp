#include <SFML/Graphics.hpp>

#define SFTK_GIZMO_GLOBAL_PROPERTIES
#include <sftk/gizmo/Gizmo.hpp>

#include <sftk/qol/QoL.hpp>
#include <sftk/print/Printer.hpp>

#include <sftk/clipper/Clipper.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Window");

    sf::CircleShape c(300);
    c.setOrigin(sftk::get_size(c.getLocalBounds()) / 2.f);
    c.setPosition(sftk::cast<float>(window.getSize()) / 2.f);

    sf::FloatRect clip_tall, clip_wide;

    {
        constexpr float width = 300;
        constexpr float padding = 50;

        auto const window_size = sftk::cast<float>(window.getSize());

        clip_tall = {
            (window_size.x - width) / 2.f, padding,
            width, window_size.y - padding * 2.f
        };

        clip_wide = {
            padding, (window_size.y - width) / 2.f,
            window_size.x - padding * 2.f, width
        };
    }

    sftk::gizmo.set_target(window).set_draw_origin(false);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                auto v = window.getView();
                v.move(-50, 0);
                window.setView(v);
            }
        }

        window.clear();

        {
            sftk::Clipper clipper(window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                clipper.add_clip(clip_wide);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                clipper.add_clip(clip_tall);
            }

            window.draw(c);
        }


        sftk::gizmo.set_color(sf::Color::Red).draw_rect(sftk::cast<int>(clip_tall)).set_color(sf::Color::Green);
        sftk::gizmo.draw_rect(sftk::cast<int>(clip_wide));
        sftk::gizmo.draw_circle(sftk::cast<int>(c.getPosition()), c.getRadius());

        window.display();
    }
}
