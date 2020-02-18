#include <SFML/Graphics.hpp>
#include <sftk/qol/QoL.hpp>
#include <sftk/nineSlice/NineSlice.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Window");

    sf::Texture gui_texture;
    if(!gui_texture.loadFromFile("/a/path/to/a/valid/texture.png")) {
        std::cerr << "Couldn't load texture's GUI\n";
        return 1;
    }

    // Define the size of the corners with the padding (left, top, right, bottom)
    auto const padding = sftk::Padding{ 5, 5, 5, 5 };
    auto const initial_size = sf::Vector2f{ 60, 20 };
    // The strategy is used when the size of the sprite is smaller than the sum of the padding
    // Clamp: The size can't be smaller than the sum of the padding
    // Crop: The corners will be cropped but not deformed (this can cause a visible seam)
    auto const initial_strategy = sftk::NineSlice::Strategy::Clamp;
    // The corners will not be scaled, the side will be scaled in one axis, the center will be scale on both axis
    sftk::NineSlice nine_slice(gui_texture, padding, initial_size, initial_strategy);
    nine_slice.scale(10, 10); // Scale the whole texture

    // Controls
    std::cout << "Move the mouse to adjust the size of the rectangle\nPress Space to change the strategy (that is used when size is smaller than the padding)\n";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseMoved) {
                // Set size of the sprite given the position of the mouse
                auto const mouse = window.mapPixelToCoords(sftk::get_mouse(event.mouseMove));
                auto const rect_end = nine_slice.getInverseTransform().transformPoint(mouse);
                nine_slice.set_size(rect_end);
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    // Change the strategy
                    auto const next = static_cast<sftk::NineSlice::Strategy>((static_cast<int>(nine_slice.get_strategy()) + 1) % 3);
                    nine_slice.set_strategy(next);
                }
            }
        }

        window.clear();
        window.draw(nine_slice);
        window.display();
    }
}
