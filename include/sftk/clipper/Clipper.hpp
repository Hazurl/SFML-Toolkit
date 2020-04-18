#pragma once

#include <SFML/Graphics.hpp>

namespace sftk {

class Clipper {
public:
	explicit Clipper(sf::RenderTarget& target_);
	explicit Clipper(sf::RenderTarget& target_, sf::FloatRect const& rect);
	~Clipper();

	Clipper(Clipper const&) = delete;
	Clipper(Clipper&&)		= delete;
	Clipper& operator=(Clipper const&) = delete;
	Clipper& operator=(Clipper&&) = delete;

	void add_clip(sf::FloatRect const& rect);

private:
	sf::RenderTarget& target;
	sf::View old_view;
};

} // namespace sftk
