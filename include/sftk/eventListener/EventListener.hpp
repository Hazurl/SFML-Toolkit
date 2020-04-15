#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

namespace sftk {
namespace details {

// Will be std::identity in c++20
struct Identity {
	template<typename T>
	constexpr inline T&& operator()(T&& t) const noexcept {
		return std::forward<T>(t);
	}
};

} // namespace details

using PropagateEvent = bool;

class EventListener {
public:
	virtual inline PropagateEvent on_close(sf::Window&) {
		return true;
	}
	virtual inline PropagateEvent on_resize(sf::Window&, sf::Event::SizeEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_lost_focus(sf::Window&) {
		return true;
	}
	virtual inline PropagateEvent on_gain_focus(sf::Window&) {
		return true;
	}
	virtual inline PropagateEvent on_text_entered(sf::Window&, sf::Event::TextEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_key_pressed(sf::Window&, sf::Event::KeyEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_key_released(sf::Window&, sf::Event::KeyEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_mouse_wheel_scrolled(sf::Window&, sf::Event::MouseWheelScrollEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_mouse_button_pressed(sf::Window&, sf::Event::MouseButtonEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_mouse_button_released(sf::Window&, sf::Event::MouseButtonEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_mouse_moved(sf::Window&, sf::Event::MouseMoveEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_mouse_entered(sf::Window&) {
		return true;
	}
	virtual inline PropagateEvent on_mouse_left(sf::Window&) {
		return true;
	}
	virtual inline PropagateEvent on_joystick_button_pressed(sf::Window&, sf::Event::JoystickButtonEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_joystick_button_released(sf::Window&, sf::Event::JoystickButtonEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_joystick_moved(sf::Window&, sf::Event::JoystickMoveEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_joystick_connected(sf::Window&, sf::Event::JoystickConnectEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_joystick_disconnected(sf::Window&, sf::Event::JoystickConnectEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_touch_began(sf::Window&, sf::Event::TouchEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_touch_moved(sf::Window&, sf::Event::TouchEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_touch_ended(sf::Window&, sf::Event::TouchEvent const&) {
		return true;
	}
	virtual inline PropagateEvent on_sensor(sf::Window&, sf::Event::SensorEvent const&) {
		return true;
	}
};

template<typename Iterator, typename F = details::Identity>
constexpr PropagateEvent
dispatch_all(sf::Window& window, sf::Event const& event, Iterator const& begin, Iterator const& end, F f = details::Identity{}) {
	switch (event.type) {
		case sf::Event::Closed: return std::all_of(begin, end, [f, &window](auto& listener) { return f(listener)->on_close(window); });
		case sf::Event::Resized:
			return std::all_of(
				begin, end, [f, &window, size_event = event.size](auto& listener) { return f(listener)->on_resize(window, size_event); });
		case sf::Event::LostFocus: return std::all_of(begin, end, [f, &window](auto& listener) { return f(listener)->on_lost_focus(window); });
		case sf::Event::GainedFocus: return std::all_of(begin, end, [f, &window](auto& listener) { return f(listener)->on_gain_focus(window); });
		case sf::Event::TextEntered:
			return std::all_of(
				begin, end, [f, &window, text_event = event.text](auto& listener) { return f(listener)->on_text_entered(window, text_event); });
		case sf::Event::KeyPressed:
			return std::all_of(
				begin, end, [f, &window, key_event = event.key](auto& listener) { return f(listener)->on_key_pressed(window, key_event); });
		case sf::Event::KeyReleased:
			return std::all_of(
				begin, end, [f, &window, key_event = event.key](auto& listener) { return f(listener)->on_key_released(window, key_event); });
		case sf::Event::MouseWheelScrolled:
			return std::all_of(begin, end, [f, &window, scroll_event = event.mouseWheelScroll](auto& listener) {
				return f(listener)->on_mouse_wheel_scrolled(window, scroll_event);
			});
		case sf::Event::MouseButtonPressed:
			return std::all_of(begin, end, [f, &window, button_event = event.mouseButton](auto& listener) {
				return f(listener)->on_mouse_button_pressed(window, button_event);
			});
		case sf::Event::MouseButtonReleased:
			return std::all_of(begin, end, [f, &window, button_event = event.mouseButton](auto& listener) {
				return f(listener)->on_mouse_button_released(window, button_event);
			});
		case sf::Event::MouseMoved:
			return std::all_of(
				begin, end, [f, &window, mouse_event = event.mouseMove](auto& listener) { return f(listener)->on_mouse_moved(window, mouse_event); });
		case sf::Event::MouseEntered: return std::all_of(begin, end, [f, &window](auto& listener) { return f(listener)->on_mouse_entered(window); });
		case sf::Event::MouseLeft: return std::all_of(begin, end, [f, &window](auto& listener) { return f(listener)->on_mouse_left(window); });
		case sf::Event::JoystickButtonPressed:
			return std::all_of(begin, end, [f, &window, button_event = event.joystickButton](auto& listener) {
				return f(listener)->on_joystick_button_pressed(window, button_event);
			});
		case sf::Event::JoystickButtonReleased:
			return std::all_of(begin, end, [f, &window, button_event = event.joystickButton](auto& listener) {
				return f(listener)->on_joystick_button_released(window, button_event);
			});
		case sf::Event::JoystickMoved:
			return std::all_of(begin, end, [f, &window, joystick_event = event.joystickMove](auto& listener) {
				return f(listener)->on_joystick_moved(window, joystick_event);
			});
		case sf::Event::JoystickConnected:
			return std::all_of(begin, end, [f, &window, joystick_event = event.joystickConnect](auto& listener) {
				return f(listener)->on_joystick_connected(window, joystick_event);
			});
		case sf::Event::JoystickDisconnected:
			return std::all_of(begin, end, [f, &window, joystick_event = event.joystickConnect](auto& listener) {
				return f(listener)->on_joystick_disconnected(window, joystick_event);
			});
		case sf::Event::TouchBegan:
			return std::all_of(
				begin, end, [f, &window, touch_event = event.touch](auto& listener) { return f(listener)->on_touch_began(window, touch_event); });
		case sf::Event::TouchMoved:
			return std::all_of(
				begin, end, [f, &window, touch_event = event.touch](auto& listener) { return f(listener)->on_touch_moved(window, touch_event); });
		case sf::Event::TouchEnded:
			return std::all_of(
				begin, end, [f, &window, touch_event = event.touch](auto& listener) { return f(listener)->on_touch_ended(window, touch_event); });
		case sf::Event::SensorChanged:
			return std::all_of(
				begin, end, [f, &window, sensor_event = event.sensor](auto& listener) { return f(listener)->on_sensor(window, sensor_event); });
		default: return true;
	}
}

inline constexpr PropagateEvent dispatch(sf::Window& window, sf::Event const& event, EventListener& listener) {
	auto list = { &listener };
	return dispatch_all(window, event, std::begin(list), std::end(list), details::Identity{});
}


} // namespace sftk