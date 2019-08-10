#pragma once

#include <SFML/Graphics.hpp>
#include <string_view>

namespace sftk {

class TextBuilder;

class FancyText : public sf::Transformable, public sf::Drawable {
public:

    FancyText(TextBuilder&& builder);
    FancyText(TextBuilder const& builder);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

//private:

    void finish_builder(TextBuilder const& builder);
    
    sf::VertexArray vertices;
    sf::FloatRect bounds;
    // pair of texture + position at which it apply
    std::vector<std::pair<sf::Texture const*, std::size_t>> textures;
};

namespace txt {

struct size_t { unsigned int size; };
struct spacing_t { float factor; };
struct line_spacing_t { float factor; };
struct color_t { sf::Color color; };
struct outline_color_t { sf::Color color; };
struct outline_thickness_t { float thickness; };

size_t size(unsigned int _size);
spacing_t spacing(float _factor);
line_spacing_t line_spacing(float _factor);
outline_color_t outline_color(sf::Color const& _color);
outline_thickness_t outline_thickness(float _thickness);

};

class TextBuilder {
public:

    TextBuilder(sf::Font const& font);

    friend TextBuilder& operator <<(TextBuilder& builder, sf::Font& font);
    friend TextBuilder& operator <<(TextBuilder& builder, txt::size_t character_size);
    friend TextBuilder& operator <<(TextBuilder& builder, txt::spacing_t spacing);
    friend TextBuilder& operator <<(TextBuilder& builder, txt::line_spacing_t line_spacing);
    friend TextBuilder& operator <<(TextBuilder& builder, sf::Color color);
    friend TextBuilder& operator <<(TextBuilder& builder, txt::outline_color_t outline_color);
    friend TextBuilder& operator <<(TextBuilder& builder, txt::outline_thickness_t outline_thickness);
    friend TextBuilder& operator <<(TextBuilder& builder, sf::Text::Style style);

    friend TextBuilder& operator <<(TextBuilder& builder, sf::String const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, std::string const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, std::string_view const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, std::wstring const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, std::wstring_view const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, sf::Uint32 unicode);

    void append(sf::Uint32 unicode);

private:

    friend FancyText;

    sf::Font const* font;
    unsigned int character_size{ 30 };
    float line_spacing_factor{ 1.0f };
    sf::Color fill_color{ sf::Color::White };
    sf::Color outline_color{ sf::Color::Black };
    float outline_thickness{ 0.0f };

    float x{ 0.0f };
    float y{ static_cast<float>(character_size) };
    float min_x{ 0.0f };
    float max_x{ 0.0f };
    float min_y{ 0.0f };
    float max_y{ 0.0f };

    sf::Uint32 previous_char{ L'\0' };

    constexpr static float SHEAR_ANGLE{ 0.209f };
    float shear{ 0.0f };
    bool is_bold{ false };
    bool is_underlined{ false };
    bool is_striketrough{ false };
    float underline_offset{ 0.0f };
    float striketrough_offset{ 0.0f };
    float line_thickness{ 0.0f };
    float underline_start{ 0.0f };
    float striketrough_start{ 0.0f };

    float whitespace_width{ 0.0f };
    float line_spacing{ 0.0f };
    float letter_spacing{ 0.0f };

    struct CharacterSizeChanged { sf::Texture const* texture; std::size_t character_position; };
    std::vector<CharacterSizeChanged> character_size_history{ { &font->getTexture(character_size), 0 } };

    sf::VertexArray vertices{ sf::Triangles };
};

template<typename T>
TextBuilder operator <<(TextBuilder&& builder, T&& t) {
    return std::move(builder << std::forward<T>(t));
}

}