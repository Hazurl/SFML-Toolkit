#pragma once

#include <sftk/eventListener/EventListener.hpp>

#include <type_traits>
#include <functional>

namespace sftk {

template<typename... Ts>
class Listener;

namespace details {

// select_invocable<Listener<...>, void, Event>

template<typename L, typename, typename...Es> 
struct select_invocable;

// Recursive case, the top-most listener is not callable with the events
template<typename T, typename...Ts, typename...Es> 
struct select_invocable<
    Listener<T, Ts...>, 
    std::enable_if_t< ! std::is_invocable_v<T, sf::Window&, Es const&...>>, 
    Es...> 
: 
    select_invocable<Listener<Ts...>, void, Es...> {};

// Result, the tom-most listener is callable with the events
template<typename T, typename...Ts, typename...Es> 
struct select_invocable<
    Listener<T, Ts...>, 
    std::enable_if_t<std::is_invocable_v<T, sf::Window&, Es const&...>>, 
    Es...
> {
    static constexpr bool value = true;
    using type = T;
    using next = Listener<Ts...>;
};

// Final case, no more listeners
template<typename...Es> 
struct select_invocable<
    Listener<>, 
    void, 
    Es...
> {
    static constexpr bool value = false;
};

template<typename CurrentListener, typename L, typename...Events>
PropagateEvent call_listener_helper(L& listener, sf::Window& window, Events const&...events) {
    using invokable = select_invocable<CurrentListener, void, Events...>;
    if constexpr (invokable::value) {
        using T = typename invokable::type;
        using NextListener = typename invokable::next;
        return std::invoke(static_cast<T&>(listener), window, events...) && call_listener_helper<NextListener>(listener, window, events...);
    } else {
        return true;
    }
}

template<typename L, typename...Events>
PropagateEvent call_listener(L& listener, sf::Window& window, Events const&...events) {
    return call_listener_helper<L>(listener, window, events...);
}

}


struct close_tag_t{};
struct lost_focus_tag_t{};
struct gain_focus_tag_t{};
struct pressed_tag_t{};
struct release_tag_t{};
struct mouse_left_tag_t{};
struct mouse_entered_tag_t{};
struct connect_tag_t{};
struct disconnect_tag_t{};
struct touch_began_tag_t{};
struct touch_moved_tag_t{};
struct touch_ended_tag_t{};

template<typename... Ts>
class Listener : public EventListener, private Ts... {

    template<typename CurrentListener, typename L, typename...Events>
    friend PropagateEvent details::call_listener_helper(L& listener, sf::Window& window, Events const&...events);

public:

    Listener(Ts... ts) : Ts(ts)... {}

    PropagateEvent on_close                     (sf::Window& window                                               ) { 
        return details::call_listener                (*this, window, close_tag_t{}); }
    PropagateEvent on_resize                    (sf::Window& window, sf::Event::SizeEvent             const& event) {
        return details::call_listener                (*this, window, event); }
    PropagateEvent on_lost_focus                (sf::Window& window                                               ) { 
        return details::call_listener                (*this, window, lost_focus_tag_t{}); }
    PropagateEvent on_gain_focus                (sf::Window& window                                               ) { 
        return details::call_listener                (*this, window, gain_focus_tag_t{}); }
    PropagateEvent on_text_entered              (sf::Window& window, sf::Event::TextEvent             const& event) { 
        return details::call_listener                (*this, window, event); }
    PropagateEvent on_key_pressed               (sf::Window& window, sf::Event::KeyEvent              const& event) { 
        return details::call_listener                (*this, window, event, pressed_tag_t{}); }
    PropagateEvent on_key_released              (sf::Window& window, sf::Event::KeyEvent              const& event) { 
        return details::call_listener                (*this, window, event, release_tag_t{}); }
    PropagateEvent on_mouse_wheel_scrolled      (sf::Window& window, sf::Event::MouseWheelScrollEvent const& event) { 
        return details::call_listener                (*this, window, event); }
    PropagateEvent on_mouse_button_pressed      (sf::Window& window, sf::Event::MouseButtonEvent      const& event) { 
        return details::call_listener                (*this, window, event, pressed_tag_t{}); }
    PropagateEvent on_mouse_button_released     (sf::Window& window, sf::Event::MouseButtonEvent      const& event) { 
        return details::call_listener                (*this, window, event, release_tag_t{}); }
    PropagateEvent on_mouse_moved               (sf::Window& window, sf::Event::MouseMoveEvent        const& event) { 
        return details::call_listener                (*this, window, event); }
    PropagateEvent on_mouse_entered             (sf::Window& window                                               ) { 
        return details::call_listener                (*this, window, mouse_entered_tag_t{}); }
    PropagateEvent on_mouse_left                (sf::Window& window                                               ) { 
        return details::call_listener                (*this, window, mouse_left_tag_t{}); }
    PropagateEvent on_joystick_button_pressed   (sf::Window& window, sf::Event::JoystickButtonEvent   const& event) { 
        return details::call_listener                (*this, window, event, pressed_tag_t{}); }
    PropagateEvent on_joystick_button_released  (sf::Window& window, sf::Event::JoystickButtonEvent   const& event) { 
        return details::call_listener                (*this, window, event, release_tag_t{}); }
    PropagateEvent on_joystick_moved            (sf::Window& window, sf::Event::JoystickMoveEvent     const& event) { 
        return details::call_listener                (*this, window, event); }
    PropagateEvent on_joystick_connected        (sf::Window& window, sf::Event::JoystickConnectEvent  const& event) { 
        return details::call_listener                (*this, window, event, connect_tag_t{}); }
    PropagateEvent on_joystick_disconnected     (sf::Window& window, sf::Event::JoystickConnectEvent  const& event) { 
        return details::call_listener                (*this, window, event, disconnect_tag_t{}); }
    PropagateEvent on_touch_began               (sf::Window& window, sf::Event::TouchEvent            const& event) { 
        return details::call_listener                (*this, window, event, touch_began_tag_t{}); }
    PropagateEvent on_touch_moved               (sf::Window& window, sf::Event::TouchEvent            const& event) { 
        return details::call_listener                (*this, window, event, touch_moved_tag_t{}); }
    PropagateEvent on_touch_ended               (sf::Window& window, sf::Event::TouchEvent            const& event) { 
        return details::call_listener                (*this, window, event, touch_ended_tag_t{}); }
    PropagateEvent on_sensor                    (sf::Window& window, sf::Event::SensorEvent           const& event) { 
        return details::call_listener                (*this, window, event); }

};

}
