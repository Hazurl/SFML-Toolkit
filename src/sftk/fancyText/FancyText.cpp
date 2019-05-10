#include <sftk/fancyText/FancyText.hpp>

#include <cmath>
#include <iostream>

namespace {

// Add an underline or strikethrough line to the vertex array
void addLine(sf::VertexArray& vertices, float startX, float endX, float lineTop, sf::Color const& color, float offset, float thickness, float outline_thickness = 0)
{
    float top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
    float bottom = top + std::floor(thickness + 0.5f);

    vertices.append(sf::Vertex(sf::Vector2f(startX - outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(endX   + outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(startX - outline_thickness, bottom + outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(startX - outline_thickness, bottom + outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(endX   + outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(endX   + outline_thickness, bottom + outline_thickness), color, sf::Vector2f(1, 1)));
}

// Add a glyph quad to the vertex array
void addGlyphQuad(sf::VertexArray& vertices, sf::Vector2f position, sf::Color const& color, sf::Glyph const& glyph, float shear, float outline_thickness = 0)
{
    float padding = 1.0;

    std::cout << '(' << glyph.bounds.left << ", " << glyph.bounds.top << " ~ " << glyph.bounds.width << ", " << glyph.bounds.height << ')' << '\n';

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

}

namespace sftk {

FancyText::FancyText(TextBuilder&& builder) : vertices{ std::move(builder.vertices) }, bounds{} { finish_builder(builder); }
FancyText::FancyText(TextBuilder const& builder) : vertices{ builder.vertices }, bounds{} { finish_builder(builder); }

void FancyText::finish_builder(TextBuilder const& builder) {
    std::cout << "character_size: " << builder.character_size << '\n';
    std::cout << "line_spacing_factor: " << builder.line_spacing_factor << '\n';
    std::cout << "outline_thickness: " << builder.outline_thickness << '\n';
    std::cout << "x: " << builder.x << '\n';
    std::cout << "y: " << builder.y << '\n';
    std::cout << "min_x: " << builder.min_x << '\n';
    std::cout << "max_x: " << builder.max_x << '\n';
    std::cout << "min_y: " << builder.min_y << '\n';
    std::cout << "max_y: " << builder.max_y << '\n';
    std::cout << "previous_char: " << builder.previous_char << '\n';
    std::cout << "shear: " << builder.shear << '\n';
    std::cout << "is_bold: " << builder.is_bold << '\n';
    std::cout << "is_underlined: " << builder.is_underlined << '\n';
    std::cout << "is_striketrough: " << builder.is_striketrough << '\n';
    std::cout << "underline_offset: " << builder.underline_offset << '\n';
    std::cout << "striketrough_offset: " << builder.striketrough_offset << '\n';
    std::cout << "line_thickness: " << builder.line_thickness << '\n';
    std::cout << "whitespace_width: " << builder.whitespace_width << '\n';
    std::cout << "line_spacing: " << builder.line_spacing << '\n';
    std::cout << "letter_spacing: " << builder.letter_spacing << '\n';

    for(auto const& history : builder.character_size_history) {
        textures.emplace_back(
            history.texture,
            history.character_position
        );
    }

    // If we're using the underlined style, add the last line
    if (builder.is_underlined && (builder.x > 0))
    {
        addLine(vertices, builder.underline_start, builder.x, builder.y, builder.fill_color, builder.underline_offset, builder.line_thickness);

        if (builder.outline_thickness != 0)
            addLine(vertices, builder.underline_start, builder.x, builder.y, builder.outline_color, builder.underline_offset, builder.line_thickness, builder.outline_thickness);
    }

    // If we're using the strike through style, add the last line across all characters
    if (builder.is_striketrough && (builder.x > 0))
    {
        addLine(vertices, builder.striketrough_start, builder.x, builder.y, builder.fill_color, builder.striketrough_offset, builder.underline_offset);

        if (builder.outline_thickness != 0)
            addLine(vertices, builder.striketrough_start, builder.x, builder.y, builder.outline_color, builder.striketrough_offset, builder.line_thickness, builder.outline_thickness);
    }

    // Update the bounding rectangle
    bounds.left = builder.min_x;
    bounds.top = builder.min_y;
    bounds.width = builder.max_x - builder.min_x;
    bounds.height = builder.max_y - builder.min_y;
/*
    // Update the vertex buffer if it is being used
    if (VertexBuffer::isAvailable())
    {
        if (m_verticesBuffer.getVertexCount() != m_vertices.getVertexCount())
            m_verticesBuffer.create(m_vertices.getVertexCount());

        if (m_vertices.getVertexCount() > 0)
            m_verticesBuffer.update(&m_vertices[0]);

        if (m_outlineVerticesBuffer.getVertexCount() != m_outlineVertices.getVertexCount())
            m_outlineVerticesBuffer.create(m_outlineVertices.getVertexCount());

        if (m_outlineVertices.getVertexCount() > 0)
            m_outlineVerticesBuffer.update(&m_outlineVertices[0]);
    }
*/
}

void FancyText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for(auto it = std::begin(textures); it != std::end(textures); ++it) {
        auto[ txt, pos ] = *it;

        auto next_it = it + 1;
        std::size_t next_pos{ next_it == std::end(textures) ? vertices.getVertexCount() : next_it->second };

        std::cout << "DRAW " << txt << ": " << pos << " -> " << next_pos << '\n';

        states.texture = txt;
        target.draw(&vertices[pos], next_pos - pos, sf::Triangles, states);
    }
}

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
    , line_thickness{ font->getUnderlineThickness(character_size) }
    , line_spacing{ font->getLineSpacing(character_size) }
    , vertices{ sf::PrimitiveType::Triangles }
{
    auto const& space_glyph = font->getGlyph(L' ', character_size, is_bold, outline_thickness);
    whitespace_width = space_glyph.advance;

    auto x_bounds = font->getGlyph(L'x', character_size, is_bold).bounds;
    striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;
}

TextBuilder& operator <<(TextBuilder& builder, sf::Font& _font) {
    // TODO: Draw underline and striketrough
    // TODO: Store the maximum character size of the current line and the index of the first vertice of the current line
    // TODO: Offset each vertices since the start of the line

    if (builder.font == &_font) { return builder; }

    builder.font = &_font;

    std::cout << "\t\tADD TEXTURE " << &builder.font->getTexture(builder.character_size) << " at " << builder.vertices.getVertexCount() << '\n';
    if (builder.character_size_history.back().character_position != builder.vertices.getVertexCount()) {
        builder.character_size_history.push_back({ &builder.font->getTexture(builder.character_size), builder.vertices.getVertexCount() });
    } else {
        builder.character_size_history.back().texture = &builder.font->getTexture(builder.character_size);
    }

    builder.underline_offset = builder.font->getUnderlinePosition(builder.character_size);
    builder.line_thickness = builder.font->getUnderlineThickness(builder.character_size);
    builder.line_spacing = builder.font->getLineSpacing(builder.character_size) * builder.line_spacing_factor;

    auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
    builder.whitespace_width = space_glyph.advance;

    auto x_bounds = builder.font->getGlyph(L'x', builder.character_size, builder.is_bold).bounds;
    builder.striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;

    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::size_t _character_size) {
    // TODO: Draw underline and striketrough
    // TODO: Store the maximum character size of the current line and the index of the first vertice of the current line
    // TODO: Offset each vertices since the start of the line

    builder.character_size = _character_size.size;
    builder.underline_offset = builder.font->getUnderlinePosition(builder.character_size);
    builder.line_thickness = builder.font->getUnderlineThickness(builder.character_size);
    builder.line_spacing = builder.font->getLineSpacing(builder.character_size) * builder.line_spacing_factor;

    auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
    builder.whitespace_width = space_glyph.advance;

    auto x_bounds = builder.font->getGlyph(L'x', builder.character_size, builder.is_bold).bounds;
    builder.striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;

    // Never empty
    std::cout << "\t\tADD TEXTURE " << &builder.font->getTexture(builder.character_size) << " at " << builder.vertices.getVertexCount() << '\n';
    if (builder.character_size_history.back().character_position != builder.vertices.getVertexCount()) {
        builder.character_size_history.push_back({ &builder.font->getTexture(_character_size.size), builder.vertices.getVertexCount() });
    } else {
        builder.character_size_history.back().texture = &builder.font->getTexture(_character_size.size);
    }

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

TextBuilder& operator <<(TextBuilder& builder, sf::Color _color) {
    if (builder.fill_color == _color) { return builder; }

    if (builder.is_underlined) {
        addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.fill_color, builder.underline_offset, builder.line_thickness);
        if (builder.outline_thickness != 0) {
            addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.outline_color, builder.underline_offset, builder.line_thickness, builder.outline_thickness);
        }
        builder.underline_start = builder.x;
    }

    if (builder.is_striketrough) {
        addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.fill_color, builder.striketrough_offset, builder.line_thickness);
        if (builder.outline_thickness != 0) {
            addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.outline_color, builder.striketrough_offset, builder.line_thickness, builder.outline_thickness);
        }
        builder.striketrough_start = builder.x;
    }

    builder.fill_color = _color;
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::outline_color_t _outline_color) {
    if (builder.outline_color == _outline_color.color) { return builder; }

    if (builder.outline_thickness != 0) {
        if (builder.is_underlined) {
            addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.fill_color, builder.underline_offset, builder.line_thickness);
            addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.outline_color, builder.underline_offset, builder.line_thickness, builder.outline_thickness);
            builder.underline_start = builder.x;
        }

        if (builder.is_striketrough) {
            addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.fill_color, builder.striketrough_offset, builder.line_thickness);
            addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.outline_color, builder.striketrough_offset, builder.line_thickness, builder.outline_thickness);
            builder.striketrough_start = builder.x;
        }
    }

    builder.outline_color = _outline_color.color;

    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::outline_thickness_t _outline_thickness) {
    if (builder.outline_thickness == _outline_thickness.thickness) { return builder; }

    if (builder.is_underlined) {
        addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.fill_color, builder.underline_offset, builder.line_thickness);
        if (builder.outline_thickness != 0) {
            addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.outline_color, builder.underline_offset, builder.line_thickness, builder.outline_thickness);
        }
        builder.underline_start = builder.x;
    }

    if (builder.is_striketrough) {
        addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.fill_color, builder.striketrough_offset, builder.line_thickness);
        if (builder.outline_thickness != 0) {
            addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.outline_color, builder.striketrough_offset, builder.line_thickness, builder.outline_thickness);
        }
        builder.striketrough_start = builder.x;
    }

    builder.outline_thickness = _outline_thickness.thickness;

    auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
    builder.whitespace_width = space_glyph.advance;

    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, sf::Text::Style _style) {
    builder.shear = _style & sf::Text::Italic ? TextBuilder::SHEAR_ANGLE : 0.0f;

    if (builder.is_underlined != (_style & sf::Text::Underlined)) {
        if (builder.is_underlined) {
            addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.fill_color, builder.underline_offset, builder.line_thickness);
            if (builder.outline_thickness != 0) {
                addLine(builder.vertices, builder.underline_start, builder.x, builder.y, builder.outline_color, builder.underline_offset, builder.line_thickness, builder.outline_thickness);
            }
        } else {
            builder.underline_start = builder.x;
        }
        builder.is_underlined = _style & sf::Text::Underlined;
    }

    if (builder.is_striketrough != (_style & sf::Text::StrikeThrough) || (builder.is_bold != (_style & sf::Text::Bold) && builder.is_striketrough)) {
        if (builder.is_striketrough) {
            addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.fill_color, builder.striketrough_offset, builder.line_thickness);
            if (builder.outline_thickness != 0) {
                addLine(builder.vertices, builder.striketrough_start, builder.x, builder.y, builder.outline_color, builder.striketrough_offset, builder.line_thickness, builder.outline_thickness);
            }
        }
        builder.striketrough_start = builder.x;
        builder.is_striketrough = _style & sf::Text::StrikeThrough;
    }

    if (builder.is_bold != (_style & sf::Text::Bold)) {
        builder.is_bold = _style & sf::Text::Bold;

        auto const& space_glyph = builder.font->getGlyph(L' ', builder.character_size, builder.is_bold, builder.outline_thickness);
        builder.whitespace_width = space_glyph.advance;

        auto x_bounds = builder.font->getGlyph(L'x', builder.character_size, builder.is_bold).bounds;
        builder.striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;
    }


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

TextBuilder operator <<(TextBuilder&& builder, sf::Color _color) {
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

void TextBuilder::append(sf::Uint32 unicode) {
    std::cout << "character_size: " << character_size << '\n';
    std::cout << "line_spacing_factor: " << line_spacing_factor << '\n';
    std::cout << "outline_thickness: " << outline_thickness << '\n';
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
    std::cout << "min_x: " << min_x << '\n';
    std::cout << "max_x: " << max_x << '\n';
    std::cout << "min_y: " << min_y << '\n';
    std::cout << "max_y: " << max_y << '\n';
    std::cout << "previous_char: " << previous_char << '\n';
    std::cout << "shear: " << shear << '\n';
    std::cout << "is_bold: " << is_bold << '\n';
    std::cout << "is_underlined: " << is_underlined << '\n';
    std::cout << "is_striketrough: " << is_striketrough << '\n';
    std::cout << "underline_offset: " << underline_offset << '\n';
    std::cout << "striketrough_offset: " << striketrough_offset << '\n';
    std::cout << "line_thickness: " << line_thickness << '\n';
    std::cout << "whitespace_width: " << whitespace_width << '\n';
    std::cout << "line_spacing: " << line_spacing << '\n';
    std::cout << "letter_spacing: " << letter_spacing << '\n';

    if (unicode == L'\r') {
        return;
    }

    std::cout << ">> KERNING: x += " << font->getKerning(previous_char, unicode, character_size) << '\n';
    x += font->getKerning(previous_char, unicode, character_size);

    // If we're using the underlined style and there's a new line, draw a line
    if (is_underlined && (unicode == L'\n' && unicode != L'\n'))
    {
        std::cout << "UNDERLINED!\n";
        addLine(vertices, underline_start, x, y, fill_color, underline_offset, line_thickness);

        if (outline_thickness != 0)
            addLine(vertices, underline_start, x, y, outline_color, underline_offset, line_thickness, outline_thickness);
    }

    // If we're using the strike through style and there's a new line, draw a line across all characters
    if (is_striketrough && (unicode == L'\n' && previous_char != L'\n'))
    {
        std::cout << "STRIKETROUGH!\n";
        addLine(vertices, striketrough_start, x, y, fill_color, striketrough_offset, line_thickness);

        if (outline_thickness != 0)
            addLine(vertices, striketrough_start, x, y, outline_color, striketrough_offset, line_thickness, outline_thickness);
    }

    previous_char = unicode;

    // Handle special characters
    if ((unicode == L' ') || (unicode == L'\n') || (unicode == L'\t'))
    {
        std::cout << "WHITESPACE!\n";
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
        std::cout << "OUTLINE!\n";
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

    std::cout << "GETGLYPH(" << unicode << ", " << character_size << ", " << is_bold << ")\n";
    // Extract the current glyph's description
    auto const& glyph = font->getGlyph(unicode, character_size, is_bold);

    std::cout << "ADDGLYPHQUAD(" << x << ", " << y << ", " << (int)fill_color.r << ", " << (int)fill_color.g << ", " << (int)fill_color.b << ", " << shear << ")\n";
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