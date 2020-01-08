#include <SFML/Graphics.hpp>

#include <sftk/print/Printer.hpp>
#include <sftk/qol/QoL.hpp>

#include <iostream>

int main() {
    sf::Vector2<float> vector2_float;
    sf::Vector2<double> vector2_double = sftk::cast<double>(vector2_float);

    sf::Vector3<float> vector3_float;
    sf::Vector3<double> vector3_double = sftk::cast<double>(vector3_float);

    sf::Rect<float> rect_float;
    sf::Rect<double> rect_double = sftk::cast<double>(rect_float);
    sf::Vector2<float> recy_position = sftk::get_position(rect_float);
    sf::Vector2<float> recy_size = sftk::get_size(rect_float);

    sf::Event::SizeEvent size_event;
    sf::Vector2<unsigned int> size_event_size = sftk::get_size(size_event);

    sf::Event::MouseMoveEvent move_event;
    sf::Vector2<int> move_event_mouse = sftk::get_mouse(move_event);

    sf::Event::MouseButtonEvent button_event;
    sf::Vector2<int> button_event_mouse = sftk::get_mouse(button_event);

    sf::Event::MouseWheelEvent wheel_event;
    sf::Vector2<int> wheel_event_mouse = sftk::get_mouse(wheel_event);

    sf::Event::MouseWheelScrollEvent wheel_scroll_event;
    sf::Vector2<int> wheel_scroll_event_mouse = sftk::get_mouse(wheel_scroll_event);

    sf::Event::TouchEvent touch_event;
    sf::Vector2<int> touch_event_touch = sftk::get_touch(touch_event);

    sf::Event::SensorEvent sensor_event;
    sf::Vector3<float> sensor_event_axis = sftk::get_sensor_axis(sensor_event);
}