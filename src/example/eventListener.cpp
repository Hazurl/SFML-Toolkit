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
}