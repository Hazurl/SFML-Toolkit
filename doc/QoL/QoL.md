# Quality of Life

This system provides some quality of life functions. Such as converting template sfml class, extracting vector/rect from events...
All of the functions are inlined, thus the library is header-only.

**Summary**
- [Vector/Rect cast](#vectorrect-cast)
- [Extraction from `sf::Rect`](#extraction-from-sfrect)
- [Extraction from events](#extraction-from-events)
- [Mapping sf::Rect's position](#mapping-sfrects-position)
- [Example](#example)

## Vector/Rect cast

You can cast `sf::Vector2<T>`, `sf::Vector3<T>` and `sf::Rect<T>` to a different `T` using these functions, it use internally `static_cast`:
```cpp
template<typename T2, typename T1> inline sf::Vector2<T2> cast(sf::Vector2<T1> const& v);
template<typename T2, typename T1> inline sf::Vector3<T2> cast(sf::Vector3<T1> const& v);
template<typename T2, typename T1> inline sf::Recr<T2> cast(sf::Rect<T1> const& v);
```

## Extraction from `sf::Rect`

The position and the size of a `sf::Rect` can be retreive with:
```cpp
template<typename T> inline sf::Vector2<T> get_position(sf::Rect<T> const& r);
template<typename T> inline sf::Vector2<T> get_size(sf::Rect<T> const& r);
```

## Extraction from events

SFML's events are not storing position/size using `sf::Vector2` or `sf::Vector3` but individual components, this libary offer quick functions that create the vectors for you:
```cpp
inline sf::Vector2<unsigned int> get_size(sf::Event::SizeEvent const& s);
inline sf::Vector2<int> get_mouse(sf::Event::MouseMoveEvent const& m);
inline sf::Vector2<int> get_mouse(sf::Event::MouseButtonEvent const& m);
inline sf::Vector2<int> get_mouse(sf::Event::MouseWheelEvent const& m);
inline sf::Vector2<int> get_mouse(sf::Event::MouseWheelScrollEvent const& m);
inline sf::Vector2<int> get_touch(sf::Event::TouchEvent const& m);
inline sf::Vector3<float> get_sensor_axis(sf::Event::SensorEvent const& m);
```

## Mapping sf::Rect's position

`sf::RenderTarget::mapCoordsToPixel` and `sf::RenderTarget::mapPixelToCoords` can map a `sf::Vector2`, these functions will map the rect's positon using them.

```cpp
inline sf::IntRect map_coords_to_pixel(sf::RenderTarget const& t, sf::FloatRect const& r);
inline sf::FloatRect map_pixel_to_coords(sf::RenderTarget const& t, sf::IntRect const& r);
```

## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/qol.cpp)

```cpp
#include <SFML/Graphics.hpp>
#include <sftk/qol/QoL.hpp>

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
```