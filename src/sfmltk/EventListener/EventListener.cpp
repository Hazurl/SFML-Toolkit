#include <sfmltk/EventListener/EventListener.hpp>

namespace sfmltk {

PropagateEvent dispatch(sf::Window& window, sf::Event const& event, EventListener& listener) {
    auto list = { &listener };
    return dispatch_all(window, event, std::begin(list), std::end(list));
}

}