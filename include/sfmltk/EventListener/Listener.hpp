#pragma once

#include <sfmltk/EventListener/EventListener.hpp>

#include <type_traits>
#include <functional>

namespace sfmltk {
namespace details {

template<typename is_zero, unsigned n, typename A, bool b, typename...Ts> 
struct _select_invocable {
    static constexpr bool value = false;
};

template<unsigned n, typename A, typename T, typename...Ts> 
struct _select_invocable<std::enable_if_t<n == 0>, n, A, true, T, Ts...> {
    static constexpr bool value = true;
    using type = T;
};

template<unsigned n, typename A, typename X, typename T, typename...Ts> 
struct _select_invocable<std::enable_if_t<n != 0>, n, A, true, X, T, Ts...> 
    : _select_invocable<void, n - 1, A, std::is_invocable_v<T, A>, T, Ts...> {};

template<unsigned n, typename A, typename X, typename T, typename...Ts> 
struct _select_invocable<void, n, A, false, X, T, Ts...> 
    : _select_invocable<void, n, A, std::is_invocable_v<T, A>, T, Ts...> {};




template<unsigned n, typename A, typename...Ts> 
struct select_invocable {
    static constexpr bool value = false;
};

template<unsigned n, typename A, typename T, typename...Ts> 
struct select_invocable<n, A, T, Ts...> 
    : _select_invocable<void, n, A, std::is_invocable_v<T, A>, T, Ts...> {};




template<typename X, typename Event, unsigned n, typename... Ts>
PropagateEvent call_listener(X& listener, Event const& t) {
    using invocable = select_invocable<n, Event, Ts...>;
    if constexpr (invocable::value) {
        using T = typename invocable::type;
        return std::invoke(static_cast<T&>(listener), t) && call_listener<X, Event, n + 1, Ts...>(listener, t);
    } else
        return true;
}

}




template<typename... Ts>
class Listener : public EventListener, private Ts... {

    template<typename X, typename Event, unsigned n, typename... Rs>
    friend PropagateEvent details::call_listener(X& listener, Event const& t);

public:

    Listener(Ts... ts) : Ts(ts)... {}

#define ON_(name, Event)\
PropagateEvent on_ ## name (event::Event const& arg) override {\
    return details::call_listener<Listener<Ts...>, event::Event, 0, Ts...>(*this, arg);\
}

    ON_(close, Closed)
    ON_(resize, Resized)
    ON_(lost_focus, LostFocus)
    ON_(gain_focus, GainFocus)
    ON_(text_entered, TextEntered)
    ON_(key_pressed, KeyPressed)
    ON_(key_released, KeyReleased)
    ON_(mouse_wheel_scrolled, MouseWheelScrolled)
    ON_(mouse_button_pressed, MouseButtonPressed)
    ON_(mouse_button_released, MouseButtonReleased)
    ON_(mouse_moved, MouseMoved)
    ON_(mouse_entered, MouseEntered)
    ON_(mouse_left, MouseLeft)
    ON_(joystick_button_pressed, JoystickButtonPressed)
    ON_(joystick_button_released, JoystickButtonReleased)
    ON_(joystick_moved, JoystickMoved)
    ON_(joystick_connected, JoystickConnected)
    ON_(joystick_disconnected, JoystickDisconnected)
    ON_(touch_began, TouchBegan)
    ON_(touch_moved, TouchMoved)
    ON_(touch_ended, TouchEnded)
    ON_(sensor, SensorChanged)

#undef ON_

};

}
