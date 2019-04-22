#include <sftk/fancyText/FancyText.hpp>
#include <cmath>

namespace sftk {

namespace txt {

size_t size(unsigned int _size) {
    return size_t { _size };
}

spacing_t spacing(float _factor) {
    return spacing_t { _factor };
}

line_spacing_t line_spacing(float _factor) {
    return line_spacing_t { _factor };
}

color_t color(sf::Color const& _color) {
    return color_t { _color };
}

outline_color_t outline_color(sf::Color const& _color) {
    return outline_color_t { _color };
}

outline_thickness_t outline_thickness(float _thickness) {
    return outline_thickness_t { _thickness };
}

}

TextBuilder::TextBuilder(sf::Font const& _font) 
    : font{ &_font }
    , underline_offset{ font->getUnderlinePosition(character_size) }
    , underline_thickness{ font->getUnderlineThickness(character_size) }
    , line_spacing{ font->getLineSpacing(character_size) }
{
    auto const& space_glyph = font->getGlyph(L' ', character_size, is_bold, outline_thickness);
    whitespace_width = space_glyph.advance;

    auto x_bounds = font->getGlyph(L'x', character_size, is_bold).bounds;
    striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;
}

TextBuilder& operator <<(TextBuilder& builder, sf::Font& _font) {
    builder.font = &_font;
    builder.underline_offset = builder.font->getUnderlinePosition(builder.character_size);
    builder.underline_thickness = builder.font->getUnderlineThickness(builder.character_size);
    builder.line_spacing = builder.font->getLineSpacing(builder.character_size) * builder.line_spacing_factor;

    auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
    builder.whitespace_width = space_glyph.advance;

    auto x_bounds = builder.font->getGlyph(L'x', builder.character_size, builder.is_bold).bounds;
    builder.striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;

    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::size_t _character_size) {
    builder.character_size = _character_size.size;
    builder.underline_offset = builder.font->getUnderlinePosition(builder.character_size);
    builder.underline_thickness = builder.font->getUnderlineThickness(builder.character_size);
    builder.line_spacing = builder.font->getLineSpacing(builder.character_size) * builder.line_spacing_factor;

    auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
    builder.whitespace_width = space_glyph.advance;

    auto x_bounds = builder.font->getGlyph(L'x', builder.character_size, builder.is_bold).bounds;
    builder.striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::spacing_t _spacing) {
    builder.letter_spacing = (builder.whitespace_width / 3.0f) * (_spacing.factor - 1.0f);
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::line_spacing_t _line_spacing) {
    builder.line_spacing_factor = _line_spacing.factor;
    builder.line_spacing = builder.font->getLineSpacing(builder.character_size) * builder.line_spacing_factor;
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::color_t _color) {
    builder.fill_color = _color.color;
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::outline_color_t _outline_color) {
    builder.outline_color = _outline_color.color;
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::outline_thickness_t _outline_thickness) {
    builder.outline_thickness = _outline_thickness.thickness;
    
    auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
    builder.whitespace_width = space_glyph.advance;

    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, sf::Text::Style _style) {
    builder.is_bold = _style & sf::Text::Bold;
    builder.is_underlined = _style & sf::Text::Underlined;
    builder.is_striketrough = _style & sf::Text::StrikeThrough;
    builder.shear = _style & sf::Text::Italic ? TextBuilder::SHEAR_ANGLE : 0.0f;

    auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
    builder.whitespace_width = space_glyph.advance;

    auto x_bounds = builder.font->getGlyph(L'x', builder.character_size, builder.is_bold).bounds;
    builder.striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;

    return builder;
}

TextBuilder operator <<(TextBuilder&& builder, sf::Font& _font) {
    return std::move(builder << _font);
}

TextBuilder operator <<(TextBuilder&& builder, txt::size_t _character_size) {
    return std::move(builder << _character_size);
}

TextBuilder operator <<(TextBuilder&& builder, txt::spacing_t _spacing) {
    return std::move(builder << _spacing);
}

TextBuilder operator <<(TextBuilder&& builder, txt::line_spacing_t _line_spacing) {
    return std::move(builder << _line_spacing);
}

TextBuilder operator <<(TextBuilder&& builder, txt::color_t _color) {
    return std::move(builder << _color);
}

TextBuilder operator <<(TextBuilder&& builder, txt::outline_color_t _outline_color) {
    return std::move(builder << _outline_color);
}

TextBuilder operator <<(TextBuilder&& builder, txt::outline_thickness_t _outline_thickness) {
    return std::move(builder << _outline_thickness);
}

TextBuilder operator <<(TextBuilder&& builder, sf::Text::Style _style) {
    return std::move(builder << _style);
}

// Add an underline or strikethrough line to the vertex array
void addLine(sf::VertexArray& vertices, float lineLength, float lineTop, sf::Color const& color, float offset, float thickness, float outline_thickness = 0)
{
    float top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
    float bottom = top + std::floor(thickness + 0.5f);

    vertices.append(sf::Vertex(sf::Vector2f(-outline_thickness,             top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(lineLength + outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(-outline_thickness,             bottom + outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(-outline_thickness,             bottom + outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(lineLength + outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(lineLength + outline_thickness, bottom + outline_thickness), color, sf::Vector2f(1, 1)));
}

// Add a glyph quad to the vertex array
void addGlyphQuad(sf::VertexArray& vertices, sf::Vector2f position, sf::Color const& color, sf::Glyph const& glyph, float shear, float outline_thickness = 0)
{
    float padding = 1.0;

    float left   = glyph.bounds.left - padding;
    float top    = glyph.bounds.top - padding;
    float right  = glyph.bounds.left + glyph.bounds.width + padding;
    float bottom = glyph.bounds.top  + glyph.bounds.height + padding;

    float u1 = static_cast<float>(glyph.textureRect.left) - padding;
    float v1 = static_cast<float>(glyph.textureRect.top) - padding;
    float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) + padding;
    float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height) + padding;

    vertices.append(sf::Vertex(sf::Vector2f(position.x + left  - shear * top    - outline_thickness, position.y + top    - outline_thickness), color, sf::Vector2f(u1, v1)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + right - shear * top    - outline_thickness, position.y + top    - outline_thickness), color, sf::Vector2f(u2, v1)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + left  - shear * bottom - outline_thickness, position.y + bottom - outline_thickness), color, sf::Vector2f(u1, v2)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + left  - shear * bottom - outline_thickness, position.y + bottom - outline_thickness), color, sf::Vector2f(u1, v2)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + right - shear * top    - outline_thickness, position.y + top    - outline_thickness), color, sf::Vector2f(u2, v1)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + right - shear * bottom - outline_thickness, position.y + bottom - outline_thickness), color, sf::Vector2f(u2, v2)));
}

void TextBuilder::append(sf::Uint32 unicode) {
    if (unicode == L'\r') {
        return;
    }

    x += font->getKerning(previous_char, unicode, character_size);

    // If we're using the underlined style and there's a new line, draw a line
    if (is_underlined && (unicode == L'\n' && unicode != L'\n'))
    {
        addLine(vertices, x, y, fill_color, underline_offset, underline_thickness);

        if (outline_thickness != 0)
            addLine(vertices, x, y, outline_color, underline_offset, underline_thickness, outline_thickness);
    }

    // If we're using the strike through style and there's a new line, draw a line across all characters
    if (is_striketrough && (unicode == L'\n' && previous_char != L'\n'))
    {
        addLine(vertices, x, y, fill_color, striketrough_offset, underline_thickness);

        if (outline_thickness != 0)
            addLine(vertices, x, y, outline_color, striketrough_offset, underline_thickness, outline_thickness);
    }

    previous_char = unicode;

    // Handle special characters
    if ((unicode == L' ') || (unicode == L'\n') || (unicode == L'\t'))
    {
        // Update the current bounds (min coordinates)
        min_x = std::min(min_x, x);
        min_y = std::min(min_y, y);

        switch (unicode)
        {
            case L' ':  x += whitespace_width;     break;
            case L'\t': x += whitespace_width * 4; break;
            case L'\n': y += line_spacing; x = 0;  break;
        }

        // Update the current bounds (max coordinates)
        max_x = std::max(max_x, x);
        max_y = std::max(max_y, y);

        // Next glyph, no need to create a quad for whitespace
        return;
    }

    // Apply the outline
    if (outline_thickness != 0)
    {
        auto const& glyph = font->getGlyph(unicode, character_size, is_bold, outline_thickness);

        float left   = glyph.bounds.left;
        float top    = glyph.bounds.top;
        float right  = glyph.bounds.left + glyph.bounds.width;
        float bottom = glyph.bounds.top  + glyph.bounds.height;

        // Add the outline glyph to the vertices
        addGlyphQuad(vertices, sf::Vector2f{ x, y }, outline_color, glyph, shear, outline_thickness);

        // Update the current bounds with the outlined glyph bounds
        min_x = std::min(min_x, x + left   - shear * bottom - outline_thickness);
        max_x = std::max(max_x, x + right  - shear * top    - outline_thickness);
        min_y = std::min(min_y, y + top    - outline_thickness);
        max_y = std::max(max_y, y + bottom - outline_thickness);
    }

    // Extract the current glyph's description
    auto const& glyph = font->getGlyph(unicode, character_size, is_bold);

    // Add the glyph to the vertices
    addGlyphQuad(vertices, sf::Vector2f{ x, y }, fill_color, glyph, shear);

    // Update the current bounds with the non outlined glyph bounds
    if (outline_thickness == 0)
    {
        float left   = glyph.bounds.left;
        float top    = glyph.bounds.top;
        float right  = glyph.bounds.left + glyph.bounds.width;
        float bottom = glyph.bounds.top  + glyph.bounds.height;

        min_x = std::min(min_x, x + left  - shear * bottom);
        max_x = std::max(max_x, x + right - shear * top);
        min_y = std::min(min_y, y + top);
        max_y = std::max(max_y, y + bottom);
    }

    // Advance to the next character
    x += glyph.advance + letter_spacing;
}

TextBuilder& operator <<(TextBuilder& builder, sf::String const& str) {
    for(auto unicode : str) {
        builder.append(unicode);
    }
    
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, std::string const& str) {
    for(auto unicode : str) {
        builder.append(static_cast<sf::Uint32>(unicode));
    }
    
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, std::string_view const& str) {
    for(auto unicode : str) {
        builder.append(static_cast<sf::Uint32>(unicode));
    }
    
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, std::wstring const& str) {
    for(auto unicode : str) {
        builder.append(static_cast<sf::Uint32>(unicode));
    }
    
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, std::wstring_view const& str) {
    for(auto unicode : str) {
        builder.append(static_cast<sf::Uint32>(unicode));
    }
    
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, sf::Uint32 unicode) {
    builder.append(unicode);
    return builder;
}

TextBuilder operator <<(TextBuilder&& builder, sf::String const& str) {
    return std::move(builder << str);
}

TextBuilder operator <<(TextBuilder&& builder, std::string const& str) {
    return std::move(builder << str);
}

TextBuilder operator <<(TextBuilder&& builder, std::string_view const& str) {
    return std::move(builder << str);
}

TextBuilder operator <<(TextBuilder&& builder, std::wstring const& str) {
    return std::move(builder << str);
}

TextBuilder operator <<(TextBuilder&& builder, std::wstring_view const& str) {
    return std::move(builder << str);
}

TextBuilder operator <<(TextBuilder&& builder, sf::Uint32 unicode) {
    return std::move(builder << unicode);
}

}