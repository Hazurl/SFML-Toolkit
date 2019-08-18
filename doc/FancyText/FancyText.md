# FancyText

This system let you create texts containging multiple styles without manually messing around with kerning. It create the text on the go to minimize the overhead. This means you won't be able to query the strings and the styles used after building it.

**Summary**
- [TextBuilder](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/FancyText/FancyText.md#textbuilder)
- [FancyText](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/FancyText/FancyText.md#fancytext)
- [Example](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/FancyText/FancyText.md#example)
- [Members details](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#members-details)

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
    if(!font.loadFromFile("/a/path/to/a/valid/font.ttf")) {
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

## Install

### Static library

```
cd ./SFML-Toolkit
make fancytext-static
cp ./build/static/libsftkfancyText.a /where/you/want
```

### Shared library

```
cd ./SFML-Toolkit
make fancytext-shared
cp ./build/shared/libsftkfancyText.so /where/you/want
```

## Members details

**Summary**:
- [`txt` namespace](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txt-namespace)
    - [`txt::size_t`, `txt::size`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtsize_t-txtsize)
    - [`txt::spacing_t`, `txt::spacing`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtspacing_t-txtspacing)
    - [`txt::line_spacing_t`, `txt::line_spacing`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtline_spacing_t-txtline_spacing)
    - [`txt::outline_color_t`, `txt::outline_color`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtoutline_color_t-txtoutline_color)
    - [`txt::outline_thickness_t`, `txt::outline_thickness`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtoutline_thickness_t-txtoutline_thickness)
    - [`styles`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#styles)
- [TextBuilder](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#textbuilder-1)
    - [Constructor](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#constructor)
    - [`append`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#append)
    - [`set_font`, `get_font`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_font-get_font)
    - [`set_character_size`, `get_character_size`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_character_size-get_character_size)
    - [`set_line_spacing`, `get_line_spacing`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_line_spacing-get_line_spacing)
    - [`set_letter_spacing`, `get_letter_spacing`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_letter_spacing-get_letter_spacing)
    - [`set_style`, `get_style`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_style-get_style)
    - [`set_fill_color`, `get_fill_color`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_fill_color-get_fill_color)
    - [`set_outline_color`, `get_outline_color`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_outline_color-get_outline_color)
    - [`set_outline_thickness`, `get_outline_thickness`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_outline_thickness-get_outline_thickness)
    - [`operator<<` with string types](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#operator-with-string-types)
- [FancyText](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#fancytext-2)
    - [Constructor](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#consructor)
    - [`get_local_bounds`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#get_local_bounds)
    - [`get_global_bounds`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#get_global_bounds)
    - [`set_text`](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#set_text)

### `txt` namespace

#### `txt::size_t`, `txt::size`

`txt::size_t` is used to notify the text builder to change the size of the characters.
You can construct it with the help of `size_t size(unsigned int _size)`.
The default size is 30. The `_size` parameter specify the size in pixels.

```cpp
using namespace sftk;
TextBuilder text_builder{ ... };
text_builder << txt::size(15);
```

#### `txt::spacing_t`, `txt::spacing`

`txt::spacing_t` is used to notify the text builder to change the letter spacing between the characters.
You can construct it with the help of `spacing_t spacing(float _factor)`.
The default letter spacing factor is 1. The `_factor` parameter specify the new spacing calculated from the font metrics and the character size. A factor below 1 bring characters closer to each other.

```cpp
using namespace sftk;
TextBuilder text_builder{ ... };
text_builder << txt::spacing(2.0f);
```

#### `txt::line_spacing_t`, `txt::line_spacing`

`txt::line_spacing_t` is used to notify the text builder to change the line spacing factor.
You can construct it with the help of `line_spacing_t line_spacing(float _factor)`. The default line spacing is 1. The `_factor` parameter specify the new line spacing proportional to the character size.

```cpp
using namespace sftk;
TextBuilder text_builder{ ... };
text_builder << txt::line_spacing(1.5f);
```

#### `txt::outline_color_t`, `txt::outline_color`

`txt::outline_color_t` is used to notify the text builder to change color of the outline.
You can construct it with the help of `outline_color_t outline_color(sf::Color _color)`. The default is opaque black. The `_color` parameter specify the new outline color of the text.

```cpp
using namespace sftk;
TextBuilder text_builder{ ... };
text_builder << txt::outline_color(sf::Color::Red);
```

#### `txt::outline_thickness_t`, `txt::outline_thickness`

`txt::outline_thickness_t` is used to notify the text builder to change the size of the outline.
You can construct it with the help of `outline_thickness_t outline_thickness(float _thickness)`. The default thickness is 0. The `_thickness` parameter specify the thickness in pixels. Negative value will cause distorded rendering.

```cpp
using namespace sftk;
TextBuilder text_builder{ ... };
text_builder << txt::outline_thickness(3.0f);
```

#### `styles`
```cpp
template<typename...Ts>
sf::Text::Style styles(Ts... ts);
```
This function helps you join multiple style. It has the same effect as `|` the style together and cast them back to `sf::Text::Style`.

### TextBuilder

#### Constructor

```cpp
TextBuilder(sf::Font const& font);
```
Construct an empty builder with the given font.

#### `append`

```cpp
void append(sf::Uint32 unicode);
TextBuilder& operator <<(TextBuilder& builder, sf::Uint32 unicode);
```
Append a single unicode character.
`\r` is not supported and will leave the text unchanged.

#### `set_font`, `get_font`

```cpp
void set_font(sf::Font& font);
TextBuilder& operator <<(TextBuilder& builder, sf::Font& font)
```
Set the font of the text for the future characters.

```cpp
sf::Font const& get_font() const;
```
Query the font currently in use.

#### `set_character_size`, `get_character_size`

```cpp
void set_character_size(unsigned int size);
TextBuilder& operator <<(TextBuilder& builder, txt::size_t character_size);
```
Set the character size for the future characters.
The default size is 30. The `size` parameter specify the size in pixels.

```cpp
unsigned int get_character_size() const;
```
Query the size currently in use.

> See also [txt::size](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtsize_t-txtsize)

#### `set_line_spacing`, `get_line_spacing`

```cpp
void set_line_spacing(float factor);
TextBuilder& operator <<(TextBuilder& builder, txt::line_spacing_t line_spacing);
```
Set the line spacing factor. The default line spacing is 1. The `factor` parameter specify the new line spacing proportional to the character size.

```cpp
float get_line_spacing() const;
```
Query the line spacing factor currently in use.

> See also [txt::line_spacing](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtline_spacing_t-txtline_spacing)

#### `set_letter_spacing`, `get_letter_spacing`

```cpp
void set_letter_spacing(float factor);
TextBuilder& operator <<(TextBuilder& builder, txt::spacing_t spacing);
```
Set the letter spacing between the characters. The default letter spacing factor is 1. The `factor` parameter specify the new spacing calculated from the font metrics and the character size. A factor below 1 bring characters closer to each other.

```cpp
float get_letter_spacing() const;
```
Query the letter spacing factor currently in use.

> See also [txt::spacing](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtspacing_t-txtspacing)

#### `set_style`, `get_style`

```cpp
void set_style(sf::Text::Style style);
TextBuilder& operator <<(TextBuilder& builder, sf::Text::Style style);
```
Set the style for the next characters. The default is `sf::Text::Style::Regular`.
Each call will override the previous style used. if you wants multiple style at once, `|` them together: `static_cast<sf::Text::Style>(sf::Text::Style::Underlined, sf::Text::Style::Italic)`.

```cpp
sf::Text::Style get_style() const;
```
Query the styles currently in use.

> See also [txt::styles](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#styles)

#### `set_fill_color`, `get_fill_color`

```cpp
void set_fill_color(sf::Color color);
TextBuilder& operator <<(TextBuilder& builder, sf::Color color);
```
Set the color of the text. The default is opaque white.  

```cpp
sf::Color get_fill_color() const;
```
Query the color currently in use.

#### `set_outline_color`, `get_outline_color`

```cpp
void set_outline_color(sf::Color color);
TextBuilder& operator <<(TextBuilder& builder, txt::outline_color_t outline_color);
```
Set the color of the outline. The default is opaque black. The `color` parameter specify the new outline color of the text.

```cpp
sf::Color get_outline_color() const;
```
Query the color currently in use.

> See also [txt::outline_color](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtoutline_color_t-txtoutline_color)

#### `set_outline_thickness`, `get_outline_thickness`

```cpp
void set_outline_thickness(float thickness);
TextBuilder& operator <<(TextBuilder& builder, txt::outline_thickness_t outline_thickness);
```
Set the thickness of the outline. The default thickness is 0. The `thickness` parameter specify the thickness in pixels. Negative value will cause distorded rendering.

```cpp
float get_outline_thickness() const;
```
Query the thickness currently in use.

> See also [txt::outline_thickness](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#txtoutline_thickness_t-txtoutline_thickness)

#### `operator<<` with string types

For ease of use, you can append the folowing strings using the `operator<<`:
- `std::string`
- `std::wstring`
- `std::string_view`
- `std::wstring_view`
- `const char*`
- `const wchar_t*`
- `sf::String`

> See also [append](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#append)

### FancyText

`FancyText` implements [`sf:Transformable`](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Transformable.php) and [`sf::Drawable`](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php) from SFML.

#### Constructor

```cpp
FancyText(sf::VertexBuffer::Usage usage = sf::VertexBuffer::Static);
FancyText(TextBuilder&& builder, sf::VertexBuffer::Usage usage = sf::VertexBuffer::Static);
FancyText(TextBuilder const& builder, sf::VertexBuffer::Usage usage = sf::VertexBuffer::Static);
```

All three constructor takes an optional parameter `usage`. It's used to initialize the internal vertex buffer (To get details about the values and their meaning checks [SFML's documentation](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1VertexBuffer.php#a3a531528684e63ecb45edd51282f5cb7)).
The first constructor initialize the object with an empty text.
The second constructor will moves the vertices from the text builder making it empty.
The third constructor will copy the vertices, the builder will still contains the vertices for future uses.

#### `get_local_bounds`

```cpp
sf::FloatRect get_local_bounds() const;
```
Get the local bounding rectangle of the entity. The returned rectangle is in local coordinates, which means that it ignores the transformations (translation, rotation, scale, ...) that are applied to the entity. In other words, this function returns the bounds of the entity in the entity's coordinate system.

#### `get_global_bounds`

```cpp
sf::FloatRect get_global_bounds() const;
```

Get the global bounding rectangle of the entity. The returned rectangle is in global coordinates, which means that it takes into account the transformations (translation, rotation, scale, ...) that are applied to the entity. In other words, this function returns the bounds of the text in the global 2D world's coordinate system.

#### `set_text`

```cpp
void set_text(TextBuilder&& builder);
void set_text(TextBuilder const& builder);
```

Similar to the [constructors](https://github.com/Hazurl/SFML-Toolkit/blob/fancy-text/doc/FancyText/FancyText.md#consructor), the first version will leave the builder empty and the other will deep copy the vertices.
In both case the new vertices will override the previous text.
