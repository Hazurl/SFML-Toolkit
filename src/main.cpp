#include <SFML/Graphics.hpp>

#define SFTK_GIZMO_GLOBAL_PROPERTIES
#include <sftk/gizmo/Gizmo.hpp>

#include <sftk/qol/QoL.hpp>
#include <sftk/print/Printer.hpp>

struct Clipping {
    sf::RenderTarget& target;
    sf::View old_view;

    Clipping(sf::RenderTarget& target_, sf::FloatRect rect) : target(target_), old_view(target.getView()) {
        auto old_size = old_view.getSize();
        auto old_position = old_view.getCenter() - old_size / 2.f;

        rect.left = std::max(rect.left, old_position.x);
        rect.top = std::max(rect.top, old_position.y);

        rect.width = std::min(rect.width, old_size.x);
        rect.height = std::min(rect.height, old_size.y);

        sf::View view(rect);
        auto size = target.getSize();
        view.setViewport(sf::FloatRect{
            rect.left / size.x,
            rect.top / size.y,
            rect.width / size.x,
            rect.height / size.y
        });
        target.setView(view);
    }

    ~Clipping() {
        target.setView(old_view);
    }
};

#define CONCAT_(a, b) a ## b
#define CONCAT(a, b) CONCAT_(a, b)

#define sftk_with_clip(...) for(struct{ bool flag; ::Clipping clipping; } CONCAT(_clipping_helper_, __LINE__) = { true, ::Clipping(__VA_ARGS__) }; CONCAT(_clipping_helper_, __LINE__).flag; CONCAT(_clipping_helper_, __LINE__).flag = false)

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::CircleShape c(50);
    c.setPosition(100, 100);

    sf::FloatRect rect{80, 110, 110, 80};

    sftk::gizmo.set_target(window).set_draw_origin(false);

    auto default_view = window.getView();
    auto default_viewport = window.getViewport(default_view);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        {
            Clipping clipping(window, {80, 110, 120, 50});
            {
                Clipping clipping(window, rect);
                window.draw(c);
            }
        }



        sftk_with_clip(window, {80, 110, 120, 50}) {
            sftk_with_clip(window, rect) {
                window.draw(c); 
            }
        }
/*
        sf::View view(rect);
        view.setViewport(sf::FloatRect{
            rect.left / window.getSize().x,
            rect.top / window.getSize().y,
            rect.width / window.getSize().x,
            rect.height / window.getSize().y
        });

        window.setView(view);
        window.draw(c);
        window.setView(default_view);
*/
        sftk::gizmo.set_color(sf::Color::Red).draw_rect(sftk::map_coords_to_pixel(window, rect)).set_color(sf::Color::Green);
        sftk::gizmo.draw_rect(sftk::map_coords_to_pixel(window, sf::FloatRect{80, 110, 120, 50}));
        sftk::gizmo.draw_circle(window.mapCoordsToPixel(c.getPosition() + sf::Vector2f{ c.getRadius(), c.getRadius() }), c.getRadius());

        window.display();
    }
}
