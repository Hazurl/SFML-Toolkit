#pragma once

#include <SFML/Graphics.hpp>

namespace sftk {

template<typename T2, typename T1>
sf::Vector2<T2> cast(sf::Vector2<T1> const& v) {
    return {
        static_cast<T2>(v.x),
        static_cast<T2>(v.y)
    };
} 

template<typename T2, typename T1>
sf::Rect<T2> cast(sf::Rect<T1> const& r) {
    return {
        static_cast<T2>(r.left),
        static_cast<T2>(r.top),
        static_cast<T2>(r.width),
        static_cast<T2>(r.height)
    };
} 

template<typename T2, typename T1>
sf::Vector3<T2> cast(sf::Vector3<T1> const& v) {
    return {
        static_cast<T2>(v.x),
        static_cast<T2>(v.y),
        static_cast<T2>(v.z)
    };
} 

template<typename T>
inline sf::Vector2<T> get_position(sf::Rect<T> const& r) {
    return {
        r.left, 
        r.top
    };
}

template<typename T>
inline sf::Vector2<T> get_size(sf::Rect<T> const& r) {
    return {
        r.width, 
        r.height
    };
}

inline sf::Vector2<unsigned int> get_size(sf::Event::SizeEvent const& s) {
    return {
        s.width, 
        s.height
    };
}

inline sf::Vector2<int> get_mouse(sf::Event::MouseMoveEvent const& m) {
    return {
        m.x, 
        m.y
    };
}

inline sf::Vector2<int> get_mouse(sf::Event::MouseButtonEvent const& m) {
    return {
        m.x, 
        m.y
    };
}

inline sf::Vector2<int> get_mouse(sf::Event::MouseWheelEvent const& m) {
    return {
        m.x, 
        m.y
    };
}

inline sf::Vector2<int> get_mouse(sf::Event::MouseWheelScrollEvent const& m) {
    return {
        m.x, 
        m.y
    };
}

inline sf::Vector2<int> get_touch(sf::Event::TouchEvent const& m) {
    return {
        m.x, 
        m.y
    };
}

inline sf::Vector3<float> get_sensor_axis(sf::Event::SensorEvent const& m) {
    return {
        m.x, 
        m.y,
        m.z
    };
}

}