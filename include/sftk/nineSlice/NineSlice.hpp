#pragma once

#include <SFML/Graphics.hpp>

namespace sftk {

struct Padding {
    unsigned left, top, right, bottom;

    constexpr bool operator==(Padding const& other) const noexcept {
        return left == other.left && right == other.right && top == other.top && bottom == other.bottom; 
    }

    constexpr bool operator!=(Padding const& other) const noexcept {
        return !(*this == other);
    }
};

class NineSlice : public sf::Transformable, public sf::Drawable {
public:

    enum class Strategy {
        Clamp, Crop, Deform
    };

private:

    using vertices_t = std::array<sf::Vertex, 54>;
    vertices_t vertices;
    Padding padding;
    sf::Texture const* texture;
    Strategy strategy;

    static vertices_t compute_vertices(sf::Texture const& texture, Padding const& padding, sf::Vector2f const& size, Strategy strategy) noexcept;
    void re_compute_vertices(sf::Vector2f const& size) noexcept;

public:

    NineSlice(sf::Texture const& texture_, Padding const& padding_, sf::Vector2f const& size, Strategy strategy_ = Strategy::Clamp) noexcept;

    void set_size(sf::Vector2f const& size) noexcept;
    sf::Vector2f get_size() const noexcept;

    Padding get_padding() const noexcept;
    void set_padding(Padding padding_) noexcept;
    sf::Texture const& getTexture() const noexcept;
    void setTexture(sf::Texture const& texture_) noexcept;

    Strategy get_strategy() const noexcept;
    void set_strategy(Strategy strategy_) noexcept;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
};

}