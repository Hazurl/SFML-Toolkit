#pragma once

#include <SFML/Graphics.hpp>
#include <string_view>

namespace sftk {

class TextBuilder;

class FancyText : public sf::Transformable, public sf::Drawable {
public:

    FancyText(sf::VertexBuffer::Usage usage = sf::VertexBuffer::Static);
    FancyText(TextBuilder&& builder, sf::VertexBuffer::Usage usage = sf::VertexBuffer::Static);
    FancyText(TextBuilder const& builder, sf::VertexBuffer::Usage usage = sf::VertexBuffer::Static);

    sf::FloatRect get_local_bounds() const;
    sf::FloatRect get_global_bounds() const;

    void set_text(TextBuilder&& builder);
    void set_text(TextBuilder const& builder);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    void finish_builder(TextBuilder const& builder);
    
    sf::VertexArray vertices;
    sf::VertexBuffer vertices_buffer;
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
outline_color_t outline_color(sf::Color _color);
outline_thickness_t outline_thickness(float _thickness);

template<typename...Ts>
sf::Text::Style styles(Ts... ts) {
    return static_cast<sf::Text::Style>(
        (sf::Text::Style::Regular | ... | sf::Text::Style{ ts })
    );
}

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
    friend TextBuilder& operator <<(TextBuilder& builder, const char* str);
    friend TextBuilder& operator <<(TextBuilder& builder, std::string_view const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, std::wstring const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, const wchar_t* str);
    friend TextBuilder& operator <<(TextBuilder& builder, std::wstring_view const& str);
    friend TextBuilder& operator <<(TextBuilder& builder, sf::Uint32 unicode);

    void append(sf::Uint32 unicode);

    void set_font(sf::Font& font);
    sf::Font const& get_font() const;

    void set_character_size(unsigned int size);
    unsigned int get_character_size() const;

    void set_line_spacing(float factor);
    float get_line_spacing() const;

    void set_letter_spacing(float factor);
    float get_letter_spacing() const;

    void set_style(sf::Text::Style style);
    sf::Text::Style get_style() const;

    void set_fill_color(sf::Color color);
    sf::Color get_fill_color() const;

    void set_outline_color(sf::Color color);
    sf::Color get_outline_color() const;

    void set_outline_thickness(float thickness);
    float get_outline_thickness() const;

private:

    void force_add_underline();
    void force_add_striketrough();
    void update_underline_offset();
    void update_line_thickness();
    void update_line_spacing();
    void update_whitespace_width();
    void update_strikethrough_offset();
    void update_letter_spacing();
    void update_texture();


    friend FancyText;

    sf::Font const* font;
    unsigned int character_size{ 30 };
    float line_spacing_factor{ 1.0f };
    float letter_spacing_factor{ 1.0f };
    sf::Color fill_color{ sf::Color::White };
    sf::Color outline_color{ sf::Color::Black };
    float outline_thickness{ 0.0f };

    float x{ 0.0f };
    float y{ 0.0f };
    float min_x{ 0.0f };
    float max_x{ 0.0f };
    float min_y{ 0.0f };
    float max_y{ 0.0f };
    float min_y_line{ 0.0f };
    float max_y_line{ 0.0f };

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

    std::size_t vertex_indice_start_of_line{ 0 };
    float max_line_spacing_since_start_of_line{ 0.0f };
    float max_line_spacing_since_start_of_line_multiplied{ 0.0f };

    float whitespace_width{ 0.0f };
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