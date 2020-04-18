#include <sftk/clipper/Clipper.hpp>

#include <cassert>

namespace sftk {

Clipper::Clipper(sf::RenderTarget& target_) : target(target_), old_view(target.getView()) {}

Clipper::Clipper(sf::RenderTarget& target_, sf::FloatRect const& rect) : Clipper(target) {
	add_clip(rect);
}

Clipper::~Clipper() {
	target.setView(old_view);
}

void Clipper::add_clip(sf::FloatRect const& rect) {
	auto current_view = target.getView();

	auto current_size	  = current_view.getSize();
	auto current_position = current_view.getCenter() - current_size / 2.f;

	rect.left = std::max(rect.left, current_position.x);
	rect.top  = std::max(rect.top, current_position.y);

	rect.width	= std::min(rect.width, current_size.x);
	rect.height = std::min(rect.height, current_size.y);

	sf::View view(rect);

	auto offset = target.mapCoordsToPixel({ rect.left, rect.top });
	sf::Rect<float> viemport_rect{ static_cast<float>(offset.x), static_cast<float>(offset.y), rect.width, rect.height };

	auto size = target.getSize();
	view.setViewport(
		sf::FloatRect{ viemport_rect.left / size.x, viemport_rect.top / size.y, viemport_rect.width / size.x, viemport_rect.height / size.y });

	target.setView(view);
}

} // namespace sftk