#include <sftk/nineSlice/NineSlice.hpp>

#include <sftk/qol/QoL.hpp>

#include <cassert>

namespace sftk {

std::pair<std::array<float, 4>, std::array<float, 4>> compute_tex_coords_and_position(float const left, float const right, float const texture_size, float const size, NineSlice::Strategy const strategy) {
    if (left + right <= size) {
        return {
            { 0.f, left, texture_size - right, texture_size },
            { 0.f, left, size - right, size },
        };
    } else if (strategy == NineSlice::Strategy::Clamp) {
        auto const clamped_size = std::max(size, left + right);
        return {
            { 0.f, left, texture_size - right, texture_size },
            { 0.f, left, clamped_size - right, clamped_size },
        };
    } else { // NineSlice::Strategy::Crop
        auto const proportion = left / (left + right) * size;
        return {
            { 0.f, proportion, texture_size - size + proportion, texture_size },
            { 0.f, proportion, proportion, size },
        };
    }
}

std::array<sf::Vertex, 54> make_grid_vertices(std::array<float, 4> const& xs, std::array<float, 4> const& ys, std::array<float, 4> const& us, std::array<float, 4> const& vs) {
    std::array<sf::Vertex, 54> vertices;

    std::size_t i = 0;
    for(std::size_t y = 0; y < 3; ++y) {
        for(std::size_t x = 0; x < 3; ++x) {
            auto const x0 = xs[x];
            auto const x1 = xs[x + 1];
            auto const y0 = ys[y];
            auto const y1 = ys[y + 1];

            auto const top_left = sf::Vector2f{ x0, y0 };
            auto const top_right = sf::Vector2f{ x1, y0 };
            auto const bottom_left = sf::Vector2f{ x0, y1 };
            auto const bottom_right = sf::Vector2f{ x1, y1 };

            auto const u0 = us[x];
            auto const u1 = us[x + 1];
            auto const v0 = vs[y];
            auto const v1 = vs[y + 1];

            auto const uv_top_left = sf::Vector2f{ u0, v0 };
            auto const uv_top_right = sf::Vector2f{ u1, v0 };
            auto const uv_bottom_left = sf::Vector2f{ u0, v1 };
            auto const uv_bottom_right = sf::Vector2f{ u1, v1 };

            vertices[i++] = sf::Vertex(bottom_left, uv_bottom_left);
            vertices[i++] = sf::Vertex(top_left, uv_top_left);
            vertices[i++] = sf::Vertex(top_right, uv_top_right);

            vertices[i++] = sf::Vertex(bottom_left, uv_bottom_left);
            vertices[i++] = sf::Vertex(top_right, uv_top_right);
            vertices[i++] = sf::Vertex(bottom_right, uv_bottom_right);
        }
    }

    assert(i == vertices.size());
    return vertices;
}

NineSlice::vertices_t NineSlice::compute_vertices(sf::Texture const& texture, Padding const& padding, sf::Vector2f const& size, Strategy strategy) noexcept {
    auto const texture_size = sftk::cast<float>(texture.getSize());
    auto[us, xs] = compute_tex_coords_and_position(static_cast<float>(padding.left), static_cast<float>(padding.right), texture_size.x, size.x, strategy);
    auto[vs, ys] = compute_tex_coords_and_position(static_cast<float>(padding.top), static_cast<float>(padding.bottom), texture_size.y, size.y, strategy);

    return make_grid_vertices(xs, ys, us, vs);
}

void NineSlice::re_compute_vertices(sf::Vector2f const& size) noexcept {
    vertices = compute_vertices(*texture, padding, size, strategy);
}

NineSlice::NineSlice(sf::Texture const& texture_, Padding const& padding_, sf::Vector2f const& size, Strategy strategy_) noexcept
    : vertices(compute_vertices(texture_, padding_, size, strategy_))
    , padding(padding_)
    , texture(&texture_)
    , strategy(strategy_)
    {}

void NineSlice::set_size(sf::Vector2f const& size) noexcept{
    re_compute_vertices(size);
}

sf::Vector2f NineSlice::get_size() const noexcept {
    return vertices.back().position;
}

Padding NineSlice::get_padding() const noexcept {
    return padding;
}

void NineSlice::set_padding(Padding padding_) noexcept {
    if (padding != padding_) {
        padding = padding_;
        re_compute_vertices(get_size());
    }
}

sf::Texture const& NineSlice::getTexture() const noexcept {
    return *texture;
}

void NineSlice::setTexture(sf::Texture const& texture_) noexcept {
    if (texture->getSize() != texture_.getSize()) {
        texture = &texture_;
        re_compute_vertices(get_size());
    } else {
        texture = &texture_;
    }
}

NineSlice::Strategy NineSlice::get_strategy() const noexcept {
    return strategy;
}

void NineSlice::set_strategy(NineSlice::Strategy strategy_) noexcept {
    if (strategy_ != strategy) {
        strategy = strategy_;
        re_compute_vertices(get_size());
    }
}

void NineSlice::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept {
    states.texture = texture;
    states.transform *= getTransform();
    target.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Triangles, states);
}

}