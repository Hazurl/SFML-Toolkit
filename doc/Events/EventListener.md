# Event Listener

This system is design to dispath events to objects that need them. 
It aims for simplicity and fast implementation.

**Summary**
- [Events](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#events)
- [EventListener](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#eventlistener)
- [Listener](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#listener)
- [Dispatcher](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#dispatcher)
- [Example](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md#example)

## Events

Each sfml's events has a new type associated with it. It contains the associated data and a reference to the `sf::Window` where the events is from.

For example, the event `sf::Event::EventType::KeyPressed` is associated with `sf::Event::KeyEvent`. His new type become `sftk::event::KeyPressed` containing the same data as `sf::Event::KeyEvent` as weel as a reference to the window.

```cpp
struct KeyPressed {
    sf::Window& window;
    sf::Keyboard::Key code;
    // other members of sf::Event::KeyEvent
    // ...
};
```

### Details

Here's the list of events:

| Sfml event type `sf::Event::Event::Type::` | Sfml event `sf::Event::` | Custom event type `sftk::event::` |
| --- | --- | --- |
| `Closed` | --- | `Closed` |
| `Resized` | `SizeEvent` | `Resized` |
| `GainFocus` | --- | `GainFocus` |
| `LostFocus` | --- | `LostFocus` | 
| `TextEntered` | `TextEvent` | `TextEntered` |
| `KeyPressed` | `KeyEvent` | `KeyPressed` |
| `KeyReleased` | `KeyEvent` | `KeyReleased` |
| `MouseWheelScrolled` | `MouseWheelScrollEvent` | `MouseWheelScrolled` |
| `MouseButtonPressed` | `MouseButtonEvent` | `MouseButtonPressed` |
| `MouseButtonReleased` | `MouseButtonEvent` | `MouseButtonReleased` |
| `MouseMoved` | `MouseMoveEvent` | `MouseMoved` |
| `MouseEntered` | --- | `MouseEntered` |
| `MouseLeft` | --- | `MouseLeft` |
| `JoystickButtonPressed` | `JoystickButtonEvent` | `JoystickButtonPressed` |
| `JoystickButtonReleased` | `JoystickButtonEvent` | `JoystickButtonReleased` |
| `JoystickMoved` | `JoystickMoveEvent` | `JoystickMoved` |
| `JoystickConnected` | `JoystickConnectEvent` | `JoystickConnected` |
| `JoystickDisconnected` | `JoystickConnectEvent` | `JoystickDisconnected` |
| `TouchBegan` | `TouchEvent` | `TouchBegan` |
| `TouchMoved` | `TouchEvent` | `TouchMoved` |
| `TouchEnded` | `TouchEvent` | `TouchEnded` |
| `SensorChanged` | `SensorEvent` | `SensorChanged` |

> **Warning**: `sf::Event::EventType::MouseWheelMoved` is deprecated so it has no associated type in `sftk::event`

## EventListener

`sftk::EventListener` is the interface you need to satisfy to works with this system.
The basic implementation is... nothing, since all methods have a default implementation.

Each methods from this interface looks like `sftk::PropagateEvent on_event_name(sftk::event::event_data const&);` where `event_name` refers to the name of the `sf::Event::EventType` in snake_case and `event_data` to his associated custom type.

`PropagateEvent` is an alias of `bool`, if the methods returns `true`, the event will continue his propagation to the other listeners, if `false` then it stop without notifying the other listeners.

### Details

Here's the list of methods you can override: 
- `PropagateEvent on_close(event::Closed const& closed);`
- `PropagateEvent on_resize(event::Resized const& resized);`
- `PropagateEvent on_lost_focus(event::LostFocus const& focus);`
- `PropagateEvent on_gain_focus(event::GainFocus const& focus);`
- `PropagateEvent on_text_entered(event::TextEntered const& text);`
- `PropagateEvent on_key_pressed(event::KeyPressed const& key);`
- `PropagateEvent on_key_released(event::KeyReleased const& key);`
- `PropagateEvent on_mouse_wheel_scrolled(event::MouseWheelScrolled const& mouse_wheel);`
- `PropagateEvent on_mouse_button_pressed(event::MouseButtonPressed const& mouse_button);`
- `PropagateEvent on_mouse_button_released(event::MouseButtonReleased const& mouse_button);`
- `PropagateEvent on_mouse_moved(event::MouseMoved const& mouse_movement);`
- `PropagateEvent on_mouse_entered(event::MouseEntered const& mouse_entered);`
- `PropagateEvent on_mouse_left(event::MouseLeft const& mouse_left);`
- `PropagateEvent on_joystick_button_pressed(event::JoystickButtonPressed const& joystick_button);`
- `PropagateEvent on_joystick_button_released(event::JoystickButtonReleased const& joystick_button);`
- `PropagateEvent on_joystick_moved(event::JoystickMoved const& joystick_movement);`
- `PropagateEvent on_joystick_connected(event::JoystickConnected const& joystick_connection);`
- `PropagateEvent on_joystick_disconnected(event::JoystickDisconnected const& joystick_disconnection);`
- `PropagateEvent on_touch_began(event::TouchBegan const& touch);`
- `PropagateEvent on_touch_moved(event::TouchMoved const& touch);`
- `PropagateEvent on_touch_ended(event::TouchEnded const& touch);`
- `PropagateEvent on_sensor(event::SensorChanged const& sensor);`

## Listener

`sftk::Listener` is an helper class that wrap any number of invocable objects into an `sftk::EventListener`. Like:
```cpp
sftk::Listener closer(
    [] (sftk::event::Closed const& c) { 
        c.window.close();
        return false; 
    },

    [] (sftk::event::KeyReleased const& k) {
        if (k.code == sf::Keyboard::Key::Escape) {
            k.window.close();
            return false;
        }
        return true;
    }
);
``` 
In this case, lamdas are used, but you can also use a class that implement the `operator()` with the events in parameters for example. The only restriction is that `std::invoke(callable, event_data)` works (aka `std::is_invocable_v<typeof(callable), typeof(event_data)>` is `true`).

## Dispatcher

Two methods are used to dispath an event to all listeners (until propagation stop):
- `template<class It> PropagateEvent dispatch_all(sf::Window& window, sf::Event const& event, It const& begin, It const& end)`
- `PropagateEvent dispatch(sf::Window& window, sf::Event const& event, EventListener const& listener)`

The first one takes a range between iterators `[begin, end)` and call the methods associated with the event. If the propagation stop, the remaining listener do not get notified. They are called in order. The dereferencing iterators must returns a pointer (or any object with `operator->`) to a `sftk::EventListener` and not a reference.
The second function is an easy-of-use for single elements.
Both functions returns if the propagation get stopped.

## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/eventListener.cpp)

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

#include <sftk/EventListener/EventListener.hpp>
#include <sftk/EventListener/Listener.hpp>

struct KeyPressedListener : sftk::EventListener {
    sftk::PropagateEvent on_key_pressed(sftk::event::KeyPressed const& k) override {
        std::cout << "Pressed `" << k.code << "`\n";
        // if it returns false, the event will not get propagated to other listeners
        return true;
    }
};

int main() {
    KeyPressedListener key_listener;

    // Listener accept any invocable objects
    sftk::Listener closer(
        // Works with any invocable objects

        [] (sftk::event::Closed const& c) { 
            c.window.close();
            return false; 
        },

        [] (sftk::event::KeyReleased const& k) {
            std::cout << "Closer's lambda A\n";
            if (k.code == sf::Keyboard::Key::Escape)
                return k.window.close(), false;
            return true;
        },
        [] (sftk::event::KeyReleased const&) {
            // only executed if the the key is not Escape, since the above function will stop the propagation if that's the case
            std::cout << "Closer's lambda B\n";
            return false;
        },
        [] (sftk::event::KeyReleased const&) {
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

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            // sftk::dispatch_all is equivalent of calling
            // sftk::dispatch on each listener if the previous returns true
            sftk::dispatch_all(window, event, std::begin(listeners), std::end(listeners));

        window.clear();
        window.display();
    }
}
```
