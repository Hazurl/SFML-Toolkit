#include <sftk/eventListener/EventListener.hpp>

namespace sftk {

PropagateEvent dispatch(sf::Window& window, sf::Event const& event, EventListener& listener) {
    auto list = { &listener };
    return dispatch_all(window, event, std::begin(list), std::end(list));
}

}