#include <SFML/Graphics.hpp>

#include <sftk/clipper/Clipper.hpp>

// You can ignore the next 50 lines
#define SFTK_GIZMO_GLOBAL_PROPERTIES
#include <sftk/gizmo/Gizmo.hpp>

#include <sftk/qol/QoL.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Window");

	sf::CircleShape c(300);
	c.setOrigin(sftk::get_size(c.getLocalBounds()) / 2.f);
	c.setPosition(sftk::cast<float>(window.getSize()) / 2.f);

	sf::FloatRect clip_tall, clip_wide;

	{
		constexpr float width	= 300;
		constexpr float padding = 50;

		auto const window_size = sftk::cast<float>(window.getSize());

		clip_tall = { (window_size.x - width) / 2.f, padding, width, window_size.y - padding * 2.f };

		clip_wide = { padding, (window_size.y - width) / 2.f, window_size.x - padding * 2.f, width };
	}

	sftk::gizmo.set_target(window).set_draw_origin(false);

	// Controls
	std::cout << "Press 'A' to create an horizontal clipper\n";
	std::cout << "Press 'Z' or 'E' to create a vertical clipper\n";
	std::cout << "Press Right to move the view 50 pixels horizontally\n";

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
				auto v = window.getView();
				v.move(-50, 0);
				window.setView(v);
			}
		}

		window.clear();

		// Create a scope to not affect the other draw call
		{
			sftk::Clipper clipper(window); // No-op

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				// (1)
				clipper.add_clip(clip_wide); // Make a horizontal clip
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				// (2)
				clipper.add_clip(clip_tall); // Make a vertical clip
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				// (3)
				auto cl = sftk::make_clipper(window, clip_tall); // Create and assign a vertical clip, added on top of `clipper`
				window.draw(c);									 // Affected by `cl` and `clipper`

				// End of scope, `cl` is destroyed, thus `clip_tall` is not bound anymore
			} else {
				window.draw(c); // Affected by `clipper`
			}

			// End of scope, `clipper` is destroyed and the window's view is restored to its state at the start of the
			// scope
		}


		// Draw the clip bounds
		sftk::gizmo.set_color(sf::Color::Red).draw_rect(sftk::cast<int>(clip_tall)).set_color(sf::Color::Green);
		sftk::gizmo.draw_rect(sftk::cast<int>(clip_wide));
		sftk::gizmo.draw_circle(sftk::cast<int>(c.getPosition()), c.getRadius());

		window.display();
	}
}
