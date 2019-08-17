# FancyText

This system let you create texts containging multiple styles without manually messing around with kerning. It create the text on the go to minimize the overhead. This means you won't be able to query the strings and the styles used after building it.

**Summary**
- [TextBuilder](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/FancyText/FancyText.md#textbuilder)
- [FancyText](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/FancyText/FancyText.md#fancytext)

## TextBuilder

This class provides the interface to, as the name describe, build the text on the go. It use a stream interface (`operator <<`) like `std::ostream`.

The folowing strings can be pass to the `TextBuilder`:
- `std::string`
- `std::wstring`
- `std::string_view`
- `std::wstring_view`
- `const char*`
- `const wchar_t*`
- `sf::String`

And individual unicode characters can be pass as `sf::Uint32`. 

The folowing styles/options can be pass to the `TextBuilder`:
- `sf::Font&`
- `sf::Color`
- `sf::Text::Style`
- `sftk::txt::size_t` using the function `sftk::txt::size` for changing the character size
- `sftk::txt::spacing_t` using the function `sftk::txt::spacing` for changing the letter spacing factor
- `sftk::txt::line_spacing_t` using the function `sftk::txt::line_spacing` for changing the line spacing factor
- `sftk::txt::outline_color_t` using the function `sftk::txt::outline_color` for changing the outline color
- `sftk::txt::outline_thickness_t` using the function `sftk::txt::outline_thickness` for changing the outline thickness

The namespace `sftk::txt` contains several functions to distinguish the different options from eachother. 
`sftk::txt::styles` is a variadic functions that `|` all styles and 
> **Note**: Each option override the previous one, if you wants multiple `sf::Text::Style` you need to `|` them (and cast back to `sf::Text::Style`), or use `sftk::txt::styles`.
> 
> Example: `builder << sftk::txt::styles(sf::Text::Bold, sf::Text::Underlined, sf::Text::Italic);`

## FancyText

`FancyText` is the actual drawable/transformable text. As `sf::Text` you can query the local/global bounds of the text.
To insert text into it, you need to call `set_text` with a builder in parameter, it will copy or move the vertices. A constructor taking a builder is also available.

> **Note**: if you didn't move the builder you can continue to push strings to it and use it with other `FancyText`.


## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/fancyText.cpp)

```cpp
#include <SFML/Graphics.hpp>

#include <sftk/fancyText/FancyText.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::Font font;
    if(!font.loadFromFile("/a/path/to/a/valid/texture.ttf")) {
        return 1;
    }

    // You can change...
    sftk::FancyText text = sftk::TextBuilder{ font }
        << "Hello, "
    // the size...
        << sftk::txt::size(45)
    // the style...
        << sf::Text::Italic
        << "this"
        << sf::Text::Regular
    // the outline...
        << sftk::txt::outline_color(sf::Color{200, 100, 0})
        << sftk::txt::outline_thickness(3)
        << " is "
        << sftk::txt::outline_thickness(0)
        << sf::Text::Bold
    // the letter spacing...
        << sftk::txt::spacing(10)
        << "BIG!\n"
        << sftk::txt::spacing(1)
    // the line spacing...
        << sftk::txt::line_spacing(2)
        << 'A' << sf::Text::StrikeThrough << 'n' << sf::Text::Regular << "d "
        << sf::Text::Underlined
    // the color...
        << 'c' << sf::Color::Red
        << 'o' << sf::Color::Green
        << 'l' << sf::Color::White
        << 'o' << sf::Color::Blue
        << 'r' << sf::Color::Magenta
        << 'e' << sf::Color::Cyan
        << 'd' << sf::Color::Yellow
        << " !";

    // Put the text in the middle
    text.setPosition(0.5f * (window.getSize().x - text.get_local_bounds().width), 0.5f * (window.getSize().y - text.get_local_bounds().height));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();

        window.draw(text);

        window.display();
    }

}
```
