# Gizmo

This module is about drawing quickly a set of primitive. It's a header-only essentially aims for debugging.

**Summary**
- [GizmoProperties](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Gizmo/Gizmo.md#gizmoproperties)

## GizmoProperties

`GizmoProperties` is the central structure. It holds the properties requires to draw primitives.
- `sf::RenderTarget* target`: Where to draw (must not be null when drawing)
- `sf::Color color`: The color of the primitives **(Default: sf::Color::Green)**
- `sf::Font font`: The font the text use (must be set before drawing text)
- `unsigned character_size`: The size of texts drawn **(Default: 20)**
- `bool draw_origin`: Each primitive has an origin, this boolean control whether or not to draw it **(Default: true)**

Each of these properties can be changed directly or by using the methods:
- `GizmoProperties& set_target(sf::RenderTarget&)`
- `GizmoProperties& set_color(sf::Color)`
- `GizmoProperties& set_font(sf::Font)`
- `GizmoProperties& set_character_size(unsigned&)`
- `GizmoProperties& set_draw_origin(bool = true)`

They have the advantage or retuning the instance, allowing to chain them:
```cpp
GizmoProperties gizmo_properties;
gizmo_properties
    .set_target(window)
    .set_color(sf::Color::Cyan)
    .set_font(font)
    .set_character_size(50)
    .set_draw_origin();
```

> Note: Don't forget to set the target before drawing anything and the font before writing text

## Drawing

- `GizmoProperties& draw_rect(sf::IntRect const& rect, float rotation_deg = 0)`: Draw the boundaries of the rectangle, the origin is drawn at the center (if `draw_origin` is true).
- `GizmoProperties& draw_point(sf::Vector2i const& point)`: Draw a point
- `GizmoProperties& draw_circle(sf::Vector2i const& center, float radius)`: Draw a circle, the origin is located at the center
- `GizmoProperties& draw_arc(sf::Vector2i const& center, float radius, float start_deg, float end_deg)`: Draw an arc of circle, `start_deg` and `end_deg` goes clock-wise and starts on the far right, the origin is at the center of the circle. 
- `GizmoProperties& draw_line(sf::Vector2i const& start, sf::Vector2i const& end)`: Draw a line between the two points, The origin is the first point.
- `GizmoProperties& draw_arrow(sf::Vector2i const& start, sf::Vector2i const& end)`: Same as `draw_line` but draw a tip for the arrow.
- `GizmoProperties& draw_text(sf::Vector2i const& origin, sf::String const& str)`: Write `str` at `origin`. The origin is drawn at `origin`.


## Global properties

If the macro `SFTK_GIZMO_GLOBAL_PROPERTIES` is defined before including the header, the variable `sftk::gizmo` will be declared. It will also declare the methods at the root of the file, allowing the shortcut `sftk::draw_point({0, 0})` instead of `my_gizmo_properties.draw_point({0, 0})`, `sftk::gizmo.draw_point({0, 0})` is also possible.

If you want to use it, I recommend to create a header that define the macro and include the Gizmo header, your header can then be included without having to define the macro again. Another solution is to pass `-DSFTK_GIZMO_GLOBAL_PROPERTIES` to your compiler flags to define the macro.

## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/gizmo.cpp)

```cpp
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
```