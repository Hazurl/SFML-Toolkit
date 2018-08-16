#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace sftk {

std::ostream& operator<<(std::ostream& os, sf::Time const& t);

std::ostream& operator<<(std::ostream& os, sf::Color const& c);

std::ostream& operator<<(std::ostream& os, sf::ContextSettings const& c);

std::ostream& operator<<(std::ostream& os, sf::Event const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::JoystickButtonEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::JoystickConnectEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::JoystickMoveEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::KeyEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::MouseButtonEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::MouseMoveEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::MouseWheelScrollEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::SensorEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::SizeEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::TextEvent const& e);
std::ostream& operator<<(std::ostream& os, sf::Event::TouchEvent const& e);

std::ostream& operator<<(std::ostream& os, sf::Joystick::Axis const& a);
std::ostream& operator<<(std::ostream& os, sf::Keyboard::Key const& k);
std::ostream& operator<<(std::ostream& os, sf::Mouse::Button const& b);
std::ostream& operator<<(std::ostream& os, sf::Mouse::Wheel const& w);
std::ostream& operator<<(std::ostream& os, sf::Sensor::Type const& s);

std::ostream& operator<<(std::ostream& os, sf::Font::Info const& f);

template<typename T>
std::ostream& operator<<(std::ostream& os, sf::Vector2<T> const& v) {
    return os << '(' << v.x << ", " << v.y << ')';
}

template<typename T>
std::ostream& operator<<(std::ostream& os, sf::Vector3<T> const& v) {
    return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

}