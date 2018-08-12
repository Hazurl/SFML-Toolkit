#pragma once

#include <SFML/Graphics.hpp>

namespace sftk {
namespace event {

#define MAKE_EVENT(name)\
struct name {\
    name(sf::Window& window) : window(window) {}\
    sf::Window& window;\
}

#define REMAKE_SF_EVENT(name, sf_event)\
struct name : sf::Event::sf_event {\
    name(sf::Window& window, sf::Event::sf_event const& event) : sf::Event::sf_event(event), window(window) {}\
    sf::Window& window;\
}

MAKE_EVENT(Closed);
REMAKE_SF_EVENT(Resized, SizeEvent);
MAKE_EVENT(GainFocus);
MAKE_EVENT(LostFocus);
REMAKE_SF_EVENT(TextEntered, TextEvent);
REMAKE_SF_EVENT(KeyPressed, KeyEvent);
REMAKE_SF_EVENT(KeyReleased, KeyEvent);
REMAKE_SF_EVENT(MouseWheelScrolled, MouseWheelScrollEvent);
REMAKE_SF_EVENT(MouseButtonPressed, MouseButtonEvent);
REMAKE_SF_EVENT(MouseButtonReleased, MouseButtonEvent);
REMAKE_SF_EVENT(MouseMoved, MouseMoveEvent);
MAKE_EVENT(MouseEntered);
MAKE_EVENT(MouseLeft);
REMAKE_SF_EVENT(JoystickButtonPressed, JoystickButtonEvent);
REMAKE_SF_EVENT(JoystickButtonReleased, JoystickButtonEvent);
REMAKE_SF_EVENT(JoystickMoved, JoystickMoveEvent);
REMAKE_SF_EVENT(JoystickConnected, JoystickConnectEvent);
REMAKE_SF_EVENT(JoystickDisconnected, JoystickConnectEvent);
REMAKE_SF_EVENT(TouchBegan, TouchEvent);
REMAKE_SF_EVENT(TouchMoved, TouchEvent);
REMAKE_SF_EVENT(TouchEnded, TouchEvent);
REMAKE_SF_EVENT(SensorChanged, SensorEvent);

#undef MAKE_EVENT
#undef REMAKE_SF_EVENT

}
}