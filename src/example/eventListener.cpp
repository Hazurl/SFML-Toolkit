#include <SFML/Graphics.hpp>

#include <sftk/eventListener/EventListener.hpp>
#include <sftk/eventListener/Listener.hpp>

#include <iostream>

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