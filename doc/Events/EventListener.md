# Event Listener

This system is design to dispath events to objects that need them. 
It aims for simplicity and fast implementation. It is a header-only library.

**Summary**
- [EventListener](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#eventlistener)
- [Listener](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#listener)
- [Dispatcher](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#dispatcher)
- [Parameters detail](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#parameterdetail)
- [Example](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#example)

## EventListener

`sftk::EventListener` is the interface you need to satisfy to works with this system.
The basic implementation is... nothing, since all methods have a default implementation.

Each methods from this interface looks like `sftk::PropagateEvent on_event_name(sf::Window&, sf::Event::X const&);` where `event_name` refers to the name of the `sf::Event::EventType` in snake_case and `X` to its associated struct (see [this table](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#parameterdetail)).

`PropagateEvent` is an alias of `bool`, if the methods returns `true`, the event will continue his propagation to the other listeners, if `false` then it stop without notifying the other listeners.

### Details

Here's the list of methods you can override: 
- `PropagateEvent on_close                     (sf::Window&                                         )`
- `PropagateEvent on_resize                    (sf::Window&, sf::Event::SizeEvent             const&)`
- `PropagateEvent on_lost_focus                (sf::Window&                                         )`
- `PropagateEvent on_gain_focus                (sf::Window&                                         )`
- `PropagateEvent on_text_entered              (sf::Window&, sf::Event::TextEvent             const&)`
- `PropagateEvent on_key_pressed               (sf::Window&, sf::Event::KeyEvent              const&)`
- `PropagateEvent on_key_released              (sf::Window&, sf::Event::KeyEvent              const&)`
- `PropagateEvent on_mouse_wheel_scrolled      (sf::Window&, sf::Event::MouseWheelScrollEvent const&)`
- `PropagateEvent on_mouse_button_pressed      (sf::Window&, sf::Event::MouseButtonEvent      const&)`
- `PropagateEvent on_mouse_button_released     (sf::Window&, sf::Event::MouseButtonEvent      const&)`
- `PropagateEvent on_mouse_moved               (sf::Window&, sf::Event::MouseMoveEvent        const&)`
- `PropagateEvent on_mouse_entered             (sf::Window&                                         )`
- `PropagateEvent on_mouse_left                (sf::Window&                                         )`
- `PropagateEvent on_joystick_button_pressed   (sf::Window&, sf::Event::JoystickButtonEvent   const&)`
- `PropagateEvent on_joystick_button_released  (sf::Window&, sf::Event::JoystickButtonEvent   const&)`
- `PropagateEvent on_joystick_moved            (sf::Window&, sf::Event::JoystickMoveEvent     const&)`
- `PropagateEvent on_joystick_connected        (sf::Window&, sf::Event::JoystickConnectEvent  const&)`
- `PropagateEvent on_joystick_disconnected     (sf::Window&, sf::Event::JoystickConnectEvent  const&)`
- `PropagateEvent on_touch_began               (sf::Window&, sf::Event::TouchEvent            const&)`
- `PropagateEvent on_touch_moved               (sf::Window&, sf::Event::TouchEvent            const&)`
- `PropagateEvent on_touch_ended               (sf::Window&, sf::Event::TouchEvent            const&)`
- `PropagateEvent on_sensor                    (sf::Window&, sf::Event::SensorEvent           const&)`

## Listener

`sftk::Listener` is an helper class that wrap any number of invocable objects into an `sftk::EventListener`. Like:
```cpp
sftk::Listener closer(
    [] (sf::Window& window, sftk::close_tag_t) { 
        window.close();
        return false; 
    },

    [] (sf::Window& window, sf::Event::KeyEvent const& k, sftk::pressed_tag_t) {
        if (k.code == sf::Keyboard::Key::Escape) {
            window.close();
            return false;
        }
        return true;
    }
);
``` 
In this case, lamdas are used, but you can also use a class that implement the `operator()` with the correct parameters, you **need** to add the [tag corresponding to the event](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#parameterdetail) if it exists.

## Dispatcher

Two methods are used to dispath an event to all listeners (until propagation stop):
- `template<class It, typename F> PropagateEvent dispatch_all(sf::Window& window, sf::Event const& event, It const& begin, It const& end, F&& f = details::Identity{})`
- `PropagateEvent dispatch(sf::Window& window, sf::Event const& event, EventListener const& listener)`

The first one takes a range between iterators `[begin, end)` and call the methods associated with the event. If the propagation stop, the remaining listener do not get notified. They are called in order. The dereferencing iterators must returns a pointer (or any object with `operator->`) to a `sftk::EventListener` and not a reference, otherwise you can use the third parameter to transform the dereferenced iterator into a pointer. For example `dispatch_all(window, event, begin, end, [] (auto& reference) { return &reference; })` with a range of reference.
The second function is an easy-of-use for single elements.

The default value of `f` won't transform the value.

## Parameters detail

Here's the table of the parameters given the sfml event:

| Sfml event type `sf::Event::EventType::` | Sfml event data `sf::Event::` | Tag `sftk::` (Only for callable in `sftk::Listeners`) |
| --- | --- | --- |
| `Closed` | --- | `closed_tag_t` |
| `Resized` | `SizeEvent` | --- |
| `GainFocus` | --- | `gain_focus_tag_t` |
| `LostFocus` | --- | `lost_focus_tag_t` | 
| `TextEntered` | `TextEvent` | --- |
| `KeyPressed` | `KeyEvent` | `pressed_tag_t` |
| `KeyReleased` | `KeyEvent` | `released_tag_t` |
| `MouseWheelScrolled` | `MouseWheelScrollEvent` | --- |
| `MouseButtonPressed` | `MouseButtonEvent` | `pressed_tag_t` |
| `MouseButtonReleased` | `MouseButtonEvent` | `released_tag_t` |
| `MouseMoved` | `MouseMoveEvent` | --- |
| `MouseEntered` | --- | `mouse_entered_tag_t` |
| `MouseLeft` | --- | `mouse_left_tag_t` |
| `JoystickButtonPressed` | `JoystickButtonEvent` | `pressed_tag_t` |
| `JoystickButtonReleased` | `JoystickButtonEvent` | `released_tag_t` |
| `JoystickMoved` | `JoystickMoveEvent` | --- |
| `JoystickConnected` | `JoystickConnectEvent` | `connect_tag_t` |
| `JoystickDisconnected` | `JoystickConnectEvent` | `disconnect_tag_t` |
| `TouchBegan` | `TouchEvent` | `touch_began_tag_t` |
| `TouchMoved` | `TouchEvent` | `touch_moved_tag_t` |
| `TouchEnded` | `TouchEvent` | `touche_ended_tag_t` |
| `SensorChanged` | `SensorEvent` | --- |

> **Warning**: `sf::Event::EventType::MouseWheelMoved` is deprecated thus not implemented

## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/eventListener.cpp)

```cpp
#include <SFML/Graphics.hpp>

#include <sftk/eventListener/EventListener.hpp>
#include <sftk/eventListener/Listener.hpp>

#include <iostream>
#include <vector>

struct KeyPressedListener : sftk::EventListener {

    KeyPressedListener(sf::Keyboard::Key k) : key_to_react_to(k) {}

    sf::Keyboard::Key key_to_react_to;

    sftk::PropagateEvent on_key_pressed(sf::Window&, sf::Event::KeyEvent const& k) override {
        if (key_to_react_to == k.code) {
            std::cout << "Pressed `" << key_to_react_to << "`\n";
            // if it returns false, the event will not get propagated to other listeners
            return false;
        }
        return true;
    }
};

int main() {
    KeyPressedListener key_listener{ sf::Keyboard::Key::Space };

    // Listener accept any invocable objects
    sftk::Listener closer(
        [] (sf::Window& window, sftk::close_tag_t) { 
            window.close();
            return false; 
        },

        [] (sf::Window& window, sf::Event::KeyEvent const& k, sftk::pressed_tag_t) {
            std::cout << "Closer's lambda A\n";
            if (k.code == sf::Keyboard::Key::Escape) {
                window.close();
                return false;
            }
            return true;
        },
        [] (sf::Window&, sf::Event::KeyEvent const&, sftk::pressed_tag_t) {
            // only executed if the the key is not Escape, since the above function will stop the propagation if that's the case
            std::cout << "Closer's lambda B\n";
            return false;
        },
        [] (sf::Window&, sf::Event::KeyEvent const&, sftk::pressed_tag_t) {
            // never executed because the above function will stop the propagation (aka it returns `false`)
            std::cout << "Closer's lambda C\n";
            return false;
        },

        [] (auto) {
            // will get called for every events (if it gets propagate until here)
            return true;
        }
    ); 
    // You can have as many list of listener as you wants
    // Just call sftk::EventListener::dispatch_all on each of them
    std::initializer_list<sftk::EventListener*> listeners = {
        &key_listener, // higher priority at the top
        &closer
    };

    std::vector<KeyPressedListener> key_listeners {
        KeyPressedListener{ sf::Keyboard::Key::Num0 },
        KeyPressedListener{ sf::Keyboard::Key::Num1 },
        KeyPressedListener{ sf::Keyboard::Key::Num2 },
        KeyPressedListener{ sf::Keyboard::Key::Num3 },
    };

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // sftk::dispatch_all is equivalent of calling
            // sftk::dispatch on each listener if the previous returns true
            sftk::dispatch_all(window, event, std::begin(listeners), std::end(listeners));
            sftk::dispatch_all(window, event, std::begin(key_listeners), std::end(key_listeners), [] (KeyPressedListener& l) { return &l; });
        }

        window.clear();
        window.display();
    }
}```
