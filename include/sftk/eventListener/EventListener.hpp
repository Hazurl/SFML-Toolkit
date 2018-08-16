#pragma once

#include <SFML/Graphics.hpp>

#include <sftk/eventListener/Event.hpp>

namespace sftk {

using PropagateEvent = bool;

class EventListener;

template<typename Iterator>
bool dispatch_all(sf::Window& window, sf::Event const& event, Iterator const& begin, Iterator const& end);
bool dispatch(sf::Window& window, sf::Event const& event, EventListener& listener);

class EventListener {
public:

    virtual PropagateEvent on_close(event::Closed const& /* closed */) { return true; }
    virtual PropagateEvent on_resize(event::Resized const& /* resized */) { return true; }
    virtual PropagateEvent on_lost_focus(event::LostFocus const& /* focus */) { return true; }
    virtual PropagateEvent on_gain_focus(event::GainFocus const& /* focus */) { return true; }
    virtual PropagateEvent on_text_entered(event::TextEntered const& /* text */) { return true; }
    virtual PropagateEvent on_key_pressed(event::KeyPressed const& /* key */) { return true; }
    virtual PropagateEvent on_key_released(event::KeyReleased const& /* key */) { return true; }
    virtual PropagateEvent on_mouse_wheel_scrolled(event::MouseWheelScrolled const& /* mouse_wheel */) { return true; }
    virtual PropagateEvent on_mouse_button_pressed(event::MouseButtonPressed const& /* mouse_button */) { return true; }
    virtual PropagateEvent on_mouse_button_released(event::MouseButtonReleased const& /* mouse_button */) { return true; }
    virtual PropagateEvent on_mouse_moved(event::MouseMoved const& /* mouse_movement */) { return true; }
    virtual PropagateEvent on_mouse_entered(event::MouseEntered const& /* mouse_entered */) { return true; }
    virtual PropagateEvent on_mouse_left(event::MouseLeft const& /* mouse_left */) { return true; }
    virtual PropagateEvent on_joystick_button_pressed(event::JoystickButtonPressed const& /* joystick_button */) { return true; }
    virtual PropagateEvent on_joystick_button_released(event::JoystickButtonReleased const& /* joystick_button */) { return true; }
    virtual PropagateEvent on_joystick_moved(event::JoystickMoved const& /* joystick_movement */) { return true; }
    virtual PropagateEvent on_joystick_connected(event::JoystickConnected const& /* joystick_connection */) { return true; }
    virtual PropagateEvent on_joystick_disconnected(event::JoystickDisconnected const& /* joystick_disconnection */) { return true; }
    virtual PropagateEvent on_touch_began(event::TouchBegan const& /* touch */) { return true; }
    virtual PropagateEvent on_touch_moved(event::TouchMoved const& /* touch */) { return true; }
    virtual PropagateEvent on_touch_ended(event::TouchEnded const& /* touch */) { return true; }
    virtual PropagateEvent on_sensor(event::SensorChanged const& /* sensor */) { return true; }

};

template<typename Iterator>
bool dispatch_all(sf::Window& window, sf::Event const& event, Iterator const& begin, Iterator const& end) {
    switch (event.type) {
        case sf::Event::Closed: 
            return std::all_of(begin, end, [&window] (auto& listener) {
                return listener->on_close(event::Closed {window});
            });
        case sf::Event::Resized: 
            return std::all_of(begin, end, [&window, size_event = event.size] (auto& listener) {
                return listener->on_resize(event::Resized {window, size_event});
            });
        case sf::Event::LostFocus: 
            return std::all_of(begin, end, [&window] (auto& listener) {
                return listener->on_lost_focus(event::LostFocus {window});
            });
        case sf::Event::GainedFocus: 
            return std::all_of(begin, end, [&window] (auto& listener) {
                return listener->on_gain_focus(event::GainFocus {window});
            });
        case sf::Event::TextEntered: 
            return std::all_of(begin, end, [&window, text_event = event.text] (auto& listener) {
                return listener->on_text_entered(event::TextEntered {window, text_event});
            });
        case sf::Event::KeyPressed: 
            return std::all_of(begin, end, [&window, key_event = event.key] (auto& listener) {
                return listener->on_key_pressed(event::KeyPressed {window, key_event});
            });
        case sf::Event::KeyReleased: 
            return std::all_of(begin, end, [&window, key_event = event.key] (auto& listener) {
                return listener->on_key_released(event::KeyReleased {window, key_event});
            });
        case sf::Event::MouseWheelScrolled: 
            return std::all_of(begin, end, [&window, scroll_event = event.mouseWheelScroll] (auto& listener) {
                return listener->on_mouse_wheel_scrolled(event::MouseWheelScrolled {window, scroll_event});
            });
        case sf::Event::MouseButtonPressed: 
            return std::all_of(begin, end, [&window, button_event = event.mouseButton] (auto& listener) {
                return listener->on_mouse_button_pressed(event::MouseButtonPressed {window, button_event});
            });
        case sf::Event::MouseButtonReleased: 
            return std::all_of(begin, end, [&window, button_event = event.mouseButton] (auto& listener) {
                return listener->on_mouse_button_released(event::MouseButtonReleased {window, button_event});
            });
        case sf::Event::MouseMoved: 
            return std::all_of(begin, end, [&window, mouse_event = event.mouseMove] (auto& listener) {
                return listener->on_mouse_moved(event::MouseMoved {window, mouse_event});
            });
        case sf::Event::MouseEntered: 
            return std::all_of(begin, end, [&window] (auto& listener) {
                return listener->on_mouse_entered(event::MouseEntered {window});
            });
        case sf::Event::MouseLeft: 
            return std::all_of(begin, end, [&window] (auto& listener) {
                return listener->on_mouse_left(event::MouseLeft {window});
            });
        case sf::Event::JoystickButtonPressed: 
            return std::all_of(begin, end, [&window, button_event = event.joystickButton] (auto& listener) {
                return listener->on_joystick_button_pressed(event::JoystickButtonPressed {window, button_event});
            });
        case sf::Event::JoystickButtonReleased: 
            return std::all_of(begin, end, [&window, button_event = event.joystickButton] (auto& listener) {
                return listener->on_joystick_button_released(event::JoystickButtonReleased {window, button_event});
            });
        case sf::Event::JoystickMoved: 
            return std::all_of(begin, end, [&window, joystick_event = event.joystickMove] (auto& listener) {
                return listener->on_joystick_moved(event::JoystickMoved {window, joystick_event});
            });
        case sf::Event::JoystickConnected: 
            return std::all_of(begin, end, [&window, joystick_event = event.joystickConnect] (auto& listener) {
                return listener->on_joystick_connected(event::JoystickConnected {window, joystick_event});
            });
        case sf::Event::JoystickDisconnected: 
            return std::all_of(begin, end, [&window, joystick_event = event.joystickConnect] (auto& listener) {
                return listener->on_joystick_disconnected(event::JoystickDisconnected {window, joystick_event});
            });
        case sf::Event::TouchBegan: 
            return std::all_of(begin, end, [&window, touch_event = event.touch] (auto& listener) {
                return listener->on_touch_began(event::TouchBegan {window, touch_event});
            });
        case sf::Event::TouchMoved: 
            return std::all_of(begin, end, [&window, touch_event = event.touch] (auto& listener) {
                return listener->on_touch_moved(event::TouchMoved {window, touch_event});
            });
        case sf::Event::TouchEnded: 
            return std::all_of(begin, end, [&window, touch_event = event.touch] (auto& listener) {
                return listener->on_touch_ended(event::TouchEnded {window, touch_event});
            });
        case sf::Event::SensorChanged: 
            return std::all_of(begin, end, [&window, sensor_event = event.sensor] (auto& listener) {
                return listener->on_sensor(event::SensorChanged {window, sensor_event});
            });
        default:
            return true;
    }
}

}