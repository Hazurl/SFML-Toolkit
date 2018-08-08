#include <SFML/Graphics.hpp>

#include <sfmltk/EventListener/EventListener.hpp>
#include <sfmltk/EventListener/Listener.hpp>

#include <iostream>

struct KeyPressedListener : sfmltk::EventListener {
    sfmltk::PropagateEvent on_key_pressed(sfmltk::event::KeyPressed const& k) override {
        std::cout << "Pressed `" << k.code << "`\n";
        // if it returns false, the event will not get propagated to other listener
        return true;
    }
};

int main() {
    KeyPressedListener key_listener;

    // Listener accept any invocable object
    sfmltk::Listener closer(
        // Works with any invocable object

        [] (sfmltk::event::Closed const& c) { 
            c.window.close();
            return false; 
        },

        [] (sfmltk::event::KeyReleased const& k) {
            std::cout << "Closer's lambda A\n";
            if (k.code == sf::Keyboard::Key::Escape)
                return k.window.close(), false;
            return true;
        },
        [] (sfmltk::event::KeyReleased const&) {
            // only executed if the the key is not Escape, since the above function will stop the propagation if that's the case
            std::cout << "Closer's lambda B\n";
            return false;
        },
        [] (sfmltk::event::KeyReleased const&) {
            // never executed because the above function will stop the propagation (aka it `return false`)
            std::cout << "Closer's lambda C\n";
            return false;
        },

        [] (auto) {
            // will get called for every events (if it gets propagate until here)
            return true;
        }
    ); 
    // You can have as many listeners queue as you wants
    // Just call sfmltk::EventListener::dispatch_all on each of them
    std::initializer_list<sfmltk::EventListener*> listeners = {
        &key_listener, // higher priority at the top
        &closer
    };

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            // sfmltk::EventListener::dispatch_all is equivalent of calling
            // sfmltk::EventListener::dispatch on each listener if the previous returns true
            sfmltk::EventListener::dispatch_all(window, event, std::begin(listeners), std::end(listeners));

        window.clear();
        window.display();
    }
}