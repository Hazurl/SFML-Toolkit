#pragma once

#include <SFML/Graphics.hpp>

namespace sftk {

class Clipper {
public:
    explicit Clipper(sf::RenderTarget& target_);
    inline ~Clipper() {
        restore();
    }

    void add_clip(sf::FloatRect rect);
    void restore();

private:

    sf::RenderTarget& target;
    sf::View old_view;
};

Clipper make_clipper(sf::RenderTarget& target_, sf::FloatRect rect);

}
