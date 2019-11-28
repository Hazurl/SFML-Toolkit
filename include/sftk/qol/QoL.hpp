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

}