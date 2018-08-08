#include <sfmltk/EventListener/EventListener.hpp>

namespace sfmltk {

bool EventListener::dispatch(sf::Window& window, sf::Event const& event, EventListener& listener) {
    auto list = { &listener };
    return EventListener::dispatch_all(window, event, std::begin(list), std::end(list));
}

}