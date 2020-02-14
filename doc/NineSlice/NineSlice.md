# Nine Slice

`NineSlice` is a drawable object that prevent the corners to deform even if the size change. It essentially divide the textures in a grid of 3 by 3 cells. The corner will not be scretched, the side will be in one axis, and the center in both axis ([wikipedia](https://en.wikipedia.org/wiki/9-slice_scaling)).

**Summary**
- [NineSlice](#nineslice)
    - [Size](#size)
    - [Padding](#padding)
    - [Strategy](#strategy)
    - [Texture](#texture)
- [Example](#example)

## NineSlice

`NineSlice` is a class that implements `sf::Transformable` and `sf::Drawable`. Additionnaly, you can control four other properties: the size, the padding, the texture and the strategy used when the size is smaller than the padding.

It can constructed with 
```cpp
NineSlice(sf::Texture const& texture_, Padding const& padding_, sf::Vector2f const& size, Strategy strategy_ = Strategy::Clamp) noexcept;
```

### Size

The size can be modified freely using 
```cpp
void set_size(sf::Vector2f const& size) noexcept;
sf::Vector2f get_size() const noexcept;
```

> Note that using `sf::Transformable::scale` may deform the corners, you need to use `set_size` to keep NineSlice's feature.

### Padding

`sftk::Padding` contains four members `left`, `top`, `right`, `bottom` (int this order). They all define the inner padding.\
For example, `sftk::Padding{ 5, 5, 5, 5 }` will not deform each corners (until 5 pixels) of the texture used.

```cpp
Padding get_padding() const noexcept;
void set_padding(Padding padding_) noexcept;
```

### Strategy

If the size requested is smaller than the padding, then different strategy can be applied:
```cpp
enum class NineSlice::Strategy {
    Clamp,  // Resize the object so that's it's never smaller than the padding
    Crop,   // Don't deform the texture but crop it, it may create visible seams depending on the texture
    Deform, // Don't modify the size and pass the UVs coordinate directly, it will deform the texture but won't create seams
};
```
The strategy can be modified using
```cpp
Strategy get_strategy() const noexcept;
void set_strategy(Strategy strategy_) noexcept;
```

### Texture

The texture sliced, can be modified using:
```cpp
sf::Texture const& get_texture() const noexcept;
void set_texture(sf::Texture const& texture_) noexcept;
```

## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/nineSlice.cpp)

```cpp
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
```