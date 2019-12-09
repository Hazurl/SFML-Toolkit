#include <SFML/Graphics.hpp>

// Define a global variable `gizmo`
#define SFTK_GIZMO_GLOBAL_PROPERTIES

// Makes sure to include the header *after* defining the macro (if you define it at all)
#include <sftk/gizmo/Gizmo.hpp>


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::Font font;
    if (!font.loadFromFile("/a/path/to/a/valid/font.ttf")) {
        return 1;
    }

    // You can declare the properties like that
    sftk::GizmoProperties my_gizmo;
    my_gizmo
        .set_target(window)
        .set_color(sf::Color::Blue); // font can only be undefined if you never write text with these properties

    // If SFTK_GIZMO_GLOBAL_PROPERTIES is defined, you can use the global variable `sftk::gizmo` instead
    sftk::gizmo
        .set_target(window)
        .set_color(sf::Color::Red)
        .set_font(font)
        .set_character_size(40);    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Methods can be chained
        my_gizmo
            .draw_arc({600, 500}, 40, 320, 260)
            .set_color(sf::Color::Green)
            .draw_closed_arc({600, 500}, 50, 300, 280)
            .set_color(sf::Color::Blue);

        // You can call the methods with the global variable
        sftk::gizmo.draw_text({ 10, 10 }, "You can\nwrite anything");
        sftk::gizmo.draw_rect({ 400, 150, 180, 35 }, 10.f);
        sftk::gizmo.draw_line({ 10, 250 }, { 200, 300 });

        // Or use the methods directly
        sftk::draw_arrow({ 10, 200 }, { 200, 400 });
        sftk::draw_circle({ 400, 400 }, 50)
            .draw_arc({ 600, 400 }, 50, 240, 30); // ... which can also be chained

        window.display();
    }
}
