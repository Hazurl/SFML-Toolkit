#include <SFML/Graphics.hpp>
#include <sftk/nineSlice/NineSlice.hpp>
#include <sftk/qol/QoL.hpp>

#define SFTK_GIZMO_GLOBAL_PROPERTIES
#include <sftk/gizmo/Gizmo.hpp>

#include <cassert>
#include <cmath>
#include <iostream>

struct Padding {
	unsigned left;
	unsigned right;
	unsigned top;
	unsigned bottom;
};

bool operator!=(Padding const& lhs, Padding const& rhs) {
	return lhs.left != rhs.left || lhs.right != rhs.right || lhs.top != rhs.top || lhs.bottom != rhs.bottom;
}

enum class MinSizeStrategy { Clamp, Proportional };

std::array<sf::Vertex, 54> make_gui_rect_vertices(
	std::array<float, 4> const& xs, std::array<float, 4> const& ys, std::array<float, 4> const& us, std::array<float, 4> const& vs) {
	std::array<sf::Vertex, 54> vertices;

	std::size_t i = 0;
	for (std::size_t y = 0; y < 3; ++y) {
		for (std::size_t x = 0; x < 3; ++x) {
			auto const x0 = xs[x];
			auto const x1 = xs[x + 1];
			auto const y0 = ys[y];
			auto const y1 = ys[y + 1];

			auto const top_left		= sf::Vector2f{ x0, y0 };
			auto const top_right	= sf::Vector2f{ x1, y0 };
			auto const bottom_left	= sf::Vector2f{ x0, y1 };
			auto const bottom_right = sf::Vector2f{ x1, y1 };

			auto const u0 = us[x];
			auto const u1 = us[x + 1];
			auto const v0 = vs[y];
			auto const v1 = vs[y + 1];

			auto const uv_top_left	   = sf::Vector2f{ u0, v0 };
			auto const uv_top_right	   = sf::Vector2f{ u1, v0 };
			auto const uv_bottom_left  = sf::Vector2f{ u0, v1 };
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

std::pair<std::array<float, 4>, std::array<float, 4>>
get_ux_or_vy(float const left, float const right, float const texture_size, float const size, MinSizeStrategy const strategy) {
	if (left + right <= size) {
		return {
			{ 0.f, left, texture_size - right, texture_size },
			{ 0.f, left, size - right, size },
		};
	} else if (strategy == MinSizeStrategy::Clamp) {
		auto const clamped_size = std::max(size, left + right);
		return {
			{ 0.f, left, texture_size - right, texture_size },
			{ 0.f, left, clamped_size - right, clamped_size },
		};
	} else { // MinSizeStrategy::Proportional
		auto const proportion = left / (left + right) * size;
		return {
			{ 0.f, proportion, texture_size - size + proportion, texture_size },
			{ 0.f, proportion, proportion, size },
		};
	}
}

std::array<sf::Vertex, 54>
make_gui_rect(sf::Texture const& texture, Padding const& padding, sf::Vector2f const& size, MinSizeStrategy const strategy) {
	auto const texture_size = sftk::cast<float>(texture.getSize());
	auto [us, xs]			= get_ux_or_vy(static_cast<float>(padding.left), static_cast<float>(padding.right), texture_size.x, size.x, strategy);
	auto [vs, ys]			= get_ux_or_vy(static_cast<float>(padding.top), static_cast<float>(padding.bottom), texture_size.y, size.y, strategy);

	return make_gui_rect_vertices(xs, ys, us, vs);
}

class GUISprite
	: public sf::Transformable
	, public sf::Drawable {
private:
	std::array<sf::Vertex, 54> vertices;
	Padding padding;
	sf::Texture const* texture;
	MinSizeStrategy strategy;

public:
	GUISprite(sf::Texture const& texture_, Padding const& padding_, sf::Vector2f const& size, MinSizeStrategy strategy_ = MinSizeStrategy::Clamp)
		: vertices(make_gui_rect(texture_, padding_, size, strategy_))
		, padding(padding_)
		, texture(&texture_)
		, strategy(strategy_) {}

	void setSize(sf::Vector2f const& size) { vertices = make_gui_rect(*texture, padding, size, strategy); }

	sf::Vector2f getSize() const { return vertices.back().position; }

	Padding getPadding() const { return padding; }

	void setPadding(Padding padding_) {
		if (padding != padding_) {
			padding	 = padding_;
			vertices = make_gui_rect(*texture, padding, getSize(), strategy);
		}
	}

	sf::Texture const& getTexture() const { return *texture; }

	void setTexture(sf::Texture const& texture_) {
		if (texture->getSize() != texture_.getSize()) {
			vertices = make_gui_rect(texture_, padding, getSize(), strategy);
		}
		texture = &texture_;
	}

	MinSizeStrategy getStrategy() const { return strategy; }

	void setStrategy(MinSizeStrategy strategy_) {
		if (strategy_ != strategy) {
			strategy = strategy_;
			vertices = make_gui_rect(*texture, padding, getSize(), strategy);
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.texture = texture;
		states.transform *= getTransform();
		target.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Triangles, states);
	}
};

template<typename T>
sf::Rect<T> make_rect(sf::Vector2<T> const& origin, sf::Vector2<T> const& size) {
	return { origin.x, origin.y, origin.x + size.x, origin.y + size.y };
}

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Window");

	sf::Texture gui_texture;
	if (!gui_texture.loadFromFile("assets/texture/gui_texture.png")) {
		std::cerr << "Couldn't load texture's GUI\n";
		return 1;
	}

	auto const padding		= Padding{ 5, 5, 5, 5 };
	auto const sftk_padding = sftk::Padding{ 5, 5, 5, 5 };
	GUISprite gui_sprite(gui_texture, padding, { 60, 20 }, MinSizeStrategy::Clamp);
	gui_sprite.scale(10, 10);

	sftk::NineSlice nine_slice(gui_texture, sftk_padding, { 60, 20 }, sftk::NineSlice::Strategy::Clamp);
	nine_slice.scale(10, 10);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::MouseMoved) {
				auto const mouse = window.mapPixelToCoords(sftk::get_mouse(event.mouseMove));
				// auto const rect_end = gui_sprite.getInverseTransform().transformPoint(mouse);
				// gui_sprite.setSize(rect_end);
				auto const rect_end = nine_slice.getInverseTransform().transformPoint(mouse);
				nine_slice.set_size(rect_end);
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					gui_sprite.setStrategy(static_cast<MinSizeStrategy>((static_cast<int>(gui_sprite.getStrategy()) + 1) % 2));
					nine_slice.set_strategy(static_cast<sftk::NineSlice::Strategy>((static_cast<int>(nine_slice.get_strategy()) + 1) % 3));
				}
			}
		}

		window.clear();
		// window.draw(gui_sprite);
		window.draw(nine_slice);
		window.display();
	}
}
