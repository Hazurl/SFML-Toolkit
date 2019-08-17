#include <sftk/fancyText/FancyText.hpp>

#include <cmath>
#include <iostream>

namespace {

// Add an underline or strikethrough line to the vertex array
void add_line(sf::VertexArray& vertices, float startX, float endX, float lineTop, sf::Color const& color, float offset, float thickness, float outline_thickness = 0)
{
    auto top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
    auto bottom = top + std::floor(thickness + 0.5f);

    vertices.append(sf::Vertex(sf::Vector2f(startX - outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(endX   + outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(startX - outline_thickness, bottom + outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(startX - outline_thickness, bottom + outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(endX   + outline_thickness, top    - outline_thickness), color, sf::Vector2f(1, 1)));
    vertices.append(sf::Vertex(sf::Vector2f(endX   + outline_thickness, bottom + outline_thickness), color, sf::Vector2f(1, 1)));
}

// Add a glyph quad to the vertex array
void add_glyph_quad(sf::VertexArray& vertices, sf::Vector2f position, sf::Color const& color, sf::Glyph const& glyph, float shear, float outline_thickness = 0)
{
    float padding = 1.0;

    // std::cout << '(' << glyph.bounds.left << ", " << glyph.bounds.top << " ~ " << glyph.bounds.width << ", " << glyph.bounds.height << ')' << '\n';

    auto left   = glyph.bounds.left - padding;
    auto top    = glyph.bounds.top - padding;
    auto right  = glyph.bounds.left + glyph.bounds.width + padding;
    auto bottom = glyph.bounds.top  + glyph.bounds.height + padding;

    auto u1 = static_cast<float>(glyph.textureRect.left) - padding;
    auto v1 = static_cast<float>(glyph.textureRect.top) - padding;
    auto u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) + padding;
    auto v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height) + padding;

    vertices.append(sf::Vertex(sf::Vector2f(position.x + left  - shear * top    - outline_thickness, position.y + top    - outline_thickness), color, sf::Vector2f(u1, v1)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + right - shear * top    - outline_thickness, position.y + top    - outline_thickness), color, sf::Vector2f(u2, v1)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + left  - shear * bottom - outline_thickness, position.y + bottom - outline_thickness), color, sf::Vector2f(u1, v2)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + left  - shear * bottom - outline_thickness, position.y + bottom - outline_thickness), color, sf::Vector2f(u1, v2)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + right - shear * top    - outline_thickness, position.y + top    - outline_thickness), color, sf::Vector2f(u2, v1)));
    vertices.append(sf::Vertex(sf::Vector2f(position.x + right - shear * bottom - outline_thickness, position.y + bottom - outline_thickness), color, sf::Vector2f(u2, v2)));
}

}

namespace sftk {

FancyText::FancyText() : vertices{}, bounds{} {}
FancyText::FancyText(TextBuilder&& builder) : vertices{ std::move(builder.vertices) }, bounds{} { finish_builder(builder); }
FancyText::FancyText(TextBuilder const& builder) : vertices{ builder.vertices }, bounds{} { finish_builder(builder); }

void FancyText::setText(TextBuilder&& builder) {
    vertices = std::move(builder.vertices);
    finish_builder(builder); 
}

void FancyText::setText(TextBuilder const& builder) {
    vertices = std::move(builder.vertices);
    finish_builder(builder); 
}

sf::FloatRect FancyText::getLocalBounds() const {
    return bounds;
}

sf::FloatRect FancyText::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}

void FancyText::finish_builder(TextBuilder const& builder) {
    // std::cout << "vertices count: " << vertices.getVertexCount() << '\n';
    // std::cout << "character_size: " << builder.character_size << '\n';
    // std::cout << "line_spacing_factor: " << builder.line_spacing_factor << '\n';
    // std::cout << "letter_spacing_factor: " << builder.letter_spacing_factor << '\n';
    // std::cout << "outline_thickness: " << builder.outline_thickness << '\n';
    // std::cout << "x: " << builder.x << '\n';
    // std::cout << "y: " << builder.y << '\n';
    // std::cout << "min_x: " << builder.min_x << '\n';
    // std::cout << "max_x: " << builder.max_x << '\n';
    // std::cout << "min_y: " << builder.min_y << '\n';
    // std::cout << "max_y: " << builder.max_y << '\n';
    // std::cout << "previous_char: " << builder.previous_char << '\n';
    // std::cout << "shear: " << builder.shear << '\n';
    // std::cout << "is_bold: " << builder.is_bold << '\n';
    // std::cout << "is_underlined: " << builder.is_underlined << '\n';
    // std::cout << "is_striketrough: " << builder.is_striketrough << '\n';
    // std::cout << "underline_offset: " << builder.underline_offset << '\n';
    // std::cout << "striketrough_offset: " << builder.striketrough_offset << '\n';
    // std::cout << "line_thickness: " << builder.line_thickness << '\n';
    // std::cout << "whitespace_width: " << builder.whitespace_width << '\n';
    // std::cout << "max_line_spacing_since_start_of_line_multiplied: " << builder.max_line_spacing_since_start_of_line_multiplied << '\n';
    // std::cout << "max_line_spacing_since_start_of_line: " << builder.max_line_spacing_since_start_of_line << '\n';
    // std::cout << "letter_spacing: " << builder.letter_spacing << '\n';

    // TODO: regroup vertices with the same texture so the minimal amount of draw call are necessary
    for(auto const& history : builder.character_size_history) {
        textures.emplace_back(
            history.texture,
            history.character_position
        );
    }

    auto max_line_spacing_since_start_of_line = std::max(builder.max_line_spacing_since_start_of_line, builder.font->getLineSpacing(builder.character_size));    
    auto max_line_spacing_since_start_of_line_multiplied = max_line_spacing_since_start_of_line * builder.line_spacing_factor;

    for(auto i = builder.vertex_indice_start_of_line; i < vertices.getVertexCount(); ++i) {
        vertices[i].position.y += max_line_spacing_since_start_of_line_multiplied;
    }

    // If we're using the underlined style, add the last line
    if (builder.is_underlined && (builder.x > 0))
    {
        add_line(vertices, builder.underline_start, builder.x, builder.y, builder.fill_color, builder.underline_offset, builder.line_thickness);

        if (builder.outline_thickness != 0)
            add_line(vertices, builder.underline_start, builder.x, builder.y, builder.outline_color, builder.underline_offset, builder.line_thickness, builder.outline_thickness);
    }

    // If we're using the strike through style, add the last line across all characters
    if (builder.is_striketrough && (builder.x > 0))
    {
        add_line(vertices, builder.striketrough_start, builder.x, builder.y, builder.fill_color, builder.striketrough_offset, builder.line_thickness);

        if (builder.outline_thickness != 0)
            add_line(vertices, builder.striketrough_start, builder.x, builder.y, builder.outline_color, builder.striketrough_offset, builder.line_thickness, builder.outline_thickness);
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

        // std::cout << "DRAW " << txt << ": " << pos << " -> " << next_pos << '\n';

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
    , max_line_spacing_since_start_of_line{ font->getLineSpacing(character_size) }
    , vertices{ sf::PrimitiveType::Triangles }
{
    update_whitespace_width();
    update_strikethrough_offset();
}

void TextBuilder::force_add_underline() {
    add_line(vertices, underline_start, x, y, fill_color, underline_offset, line_thickness);

    if (outline_thickness != 0) {
        add_line(vertices, underline_start, x, y, outline_color, underline_offset, line_thickness, outline_thickness);
    }
}

void TextBuilder::force_add_striketrough() {
    add_line(vertices, striketrough_start, x, y, fill_color, striketrough_offset, line_thickness);

    if (outline_thickness != 0) {
        add_line(vertices, striketrough_start, x, y, outline_color, striketrough_offset, line_thickness, outline_thickness);
    }
}

void TextBuilder::update_underline_offset() {
    underline_offset = font->getUnderlinePosition(character_size);
}

void TextBuilder::update_line_thickness() {
    line_thickness = font->getUnderlineThickness(character_size);
}

void TextBuilder::update_line_spacing() {
    max_line_spacing_since_start_of_line = std::max(max_line_spacing_since_start_of_line, font->getLineSpacing(character_size));
    max_line_spacing_since_start_of_line_multiplied = max_line_spacing_since_start_of_line * line_spacing_factor;
}

void TextBuilder::update_whitespace_width() {
    auto const& space_glyph = font->getGlyph(L' ', character_size, is_bold, outline_thickness);
    whitespace_width = space_glyph.advance;
    update_letter_spacing();
}

void TextBuilder::update_strikethrough_offset() {
    auto x_bounds = font->getGlyph(L'x', character_size, is_bold).bounds;
    striketrough_offset = x_bounds.top + x_bounds.height / 2.0f;
}

void TextBuilder::update_letter_spacing() {
    letter_spacing = (whitespace_width / 3.0f) * (letter_spacing_factor - 1.0f);
}

void TextBuilder::update_texture() {
    if (character_size_history.back().character_position != vertices.getVertexCount()) {
        character_size_history.push_back({ &font->getTexture(character_size), vertices.getVertexCount() });
    } else {
        character_size_history.back().texture = &font->getTexture(character_size);
    }

}

TextBuilder& operator <<(TextBuilder& builder, sf::Font& _font) {
    // TODO: Store the maximum character size of the current line and the index of the first vertice of the current line
    // TODO: Offset each vertices since the start of the line

    if (builder.font == &_font) { return builder; }

    // If we're using the underlined style, add the last line
    if (builder.is_underlined && (builder.x > 0))
    {
        builder.force_add_underline();
        builder.underline_start = builder.x;
    }

    // If we're using the strike through style, add the last line across all characters
    if (builder.is_striketrough && (builder.x > 0))
    {
        builder.force_add_striketrough();
        builder.striketrough_start = builder.x;
    }


    builder.font = &_font;

    // std::cout << "\t\tADD TEXTURE " << &builder.font->getTexture(builder.character_size) << " at " << builder.vertices.getVertexCount() << '\n';
    builder.update_texture();

    builder.update_underline_offset();
    // std::cout << "############# thickness: " << builder.line_thickness;
    builder.update_line_thickness();
    // std::cout << " -> " << builder.line_thickness << '\n';
    builder.update_line_spacing();

    builder.update_whitespace_width();
    builder.update_strikethrough_offset();

    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::size_t _character_size) {
    // TODO: Store the maximum character size of the current line and the index of the first vertice of the current line
    // TODO: Offset each vertices since the start of the line

    if(builder.character_size == _character_size.size) return builder;

    // If we're using the underlined style, add the last line
    if (builder.is_underlined && (builder.x > 0))
    {
        builder.force_add_underline();
        builder.underline_start = builder.x;
    }

    // If we're using the strike through style, add the last line across all characters
    if (builder.is_striketrough && (builder.x > 0))
    {
        builder.force_add_striketrough();
        builder.striketrough_start = builder.x;
    }

    builder.character_size = _character_size.size;
    builder.update_underline_offset();
    builder.update_line_thickness();
    builder.update_line_spacing();

    builder.update_whitespace_width();
    builder.update_strikethrough_offset();

    // std::cout << "\t\tADD TEXTURE " << &builder.font->getTexture(builder.character_size) << " at " << builder.vertices.getVertexCount() << '\n';
    builder.update_texture();
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::spacing_t _spacing) {
    builder.letter_spacing_factor = _spacing.factor;
    builder.update_letter_spacing();
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::line_spacing_t _line_spacing) {
    builder.line_spacing_factor = _line_spacing.factor;
    builder.max_line_spacing_since_start_of_line_multiplied = builder.max_line_spacing_since_start_of_line * builder.line_spacing_factor;
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, sf::Color _color) {
    if (builder.fill_color == _color) { return builder; }

    if (builder.is_underlined) {
        builder.force_add_underline();
        builder.underline_start = builder.x;
    }

    if (builder.is_striketrough) {
        builder.force_add_striketrough();
        builder.striketrough_start = builder.x;
    }

    builder.fill_color = _color;
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::outline_color_t _outline_color) {
    if (builder.outline_color == _outline_color.color) { return builder; }

    if (builder.outline_thickness != 0) {
        if (builder.is_underlined) {
            builder.force_add_underline();
            builder.underline_start = builder.x;
        }

        if (builder.is_striketrough) {
            builder.force_add_striketrough();
            builder.striketrough_start = builder.x;
        }
    }

    builder.outline_color = _outline_color.color;

    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, txt::outline_thickness_t _outline_thickness) {
    if (builder.outline_thickness == _outline_thickness.thickness) { return builder; }

    if (builder.is_underlined) {
        builder.force_add_underline();
        builder.underline_start = builder.x;
    }

    if (builder.is_striketrough) {
        builder.force_add_striketrough();
        builder.striketrough_start = builder.x;
    }

    builder.outline_thickness = _outline_thickness.thickness;

    builder.update_whitespace_width();
    builder.update_letter_spacing();
    return builder;
}

TextBuilder& operator <<(TextBuilder& builder, sf::Text::Style _style) {
    builder.shear = _style & sf::Text::Italic ? TextBuilder::SHEAR_ANGLE : 0.0f;

    if (builder.is_underlined != (_style & sf::Text::Underlined)) {
        if (builder.is_underlined) {
            builder.force_add_underline();
        } else {
            builder.underline_start = builder.x;
        }
        builder.is_underlined = _style & sf::Text::Underlined;
    }

    if (builder.is_striketrough != (_style & sf::Text::StrikeThrough) || (builder.is_bold != (_style & sf::Text::Bold) && builder.is_striketrough)) {
        if (builder.is_striketrough) {
            builder.force_add_striketrough();
        }
        builder.striketrough_start = builder.x;
        builder.is_striketrough = _style & sf::Text::StrikeThrough;
    }

    if (builder.is_bold != (_style & sf::Text::Bold)) {
        builder.is_bold = _style & sf::Text::Bold;

        builder.update_whitespace_width();
        builder.update_strikethrough_offset();
        builder.update_letter_spacing();
    }


    return builder;
}

void TextBuilder::append(sf::Uint32 unicode) {
    // std::cout << "\n################\n";
    // std::cout << "vertices count: " << vertices.getVertexCount() << '\n';
    // std::cout << "character_size: " << character_size << '\n';
    // std::cout << "line_spacing_factor: " << line_spacing_factor << '\n';
    // std::cout << "letter_spacing_factor: " << letter_spacing_factor << '\n';
    // std::cout << "outline_thickness: " << outline_thickness << '\n';
    // std::cout << "x: " << x << '\n';
    // std::cout << "y: " << y << '\n';
    // std::cout << "min_x: " << min_x << '\n';
    // std::cout << "max_x: " << max_x << '\n';
    // std::cout << "min_y: " << min_y << '\n';
    // std::cout << "max_y: " << max_y << '\n';
    // std::cout << "previous_char: " << previous_char << '\n';
    // std::cout << "shear: " << shear << '\n';
    // std::cout << "is_bold: " << is_bold << '\n';
    // std::cout << "is_underlined: " << is_underlined << '\n';
    // std::cout << "is_striketrough: " << is_striketrough << '\n';
    // std::cout << "underline_offset: " << underline_offset << '\n';
    // std::cout << "striketrough_offset: " << striketrough_offset << '\n';
    // std::cout << "line_thickness: " << line_thickness << '\n';
    // std::cout << "whitespace_width: " << whitespace_width << '\n';
    // std::cout << "max_line_spacing_since_start_of_line_multiplied: " << max_line_spacing_since_start_of_line_multiplied << '\n';
    // std::cout << "max_line_spacing_since_start_of_line: " << max_line_spacing_since_start_of_line << '\n';
    // std::cout << "letter_spacing: " << letter_spacing << '\n';

    if (unicode == L'\r') {
        return;
    }

    update_line_spacing();

    // std::cout << ">> KERNING: x += " << font->getKerning(previous_char, unicode, character_size) << '\n';
    x += font->getKerning(previous_char, unicode, character_size);

    // If we're using the underlined style and there's a new line, draw a line
    if (is_underlined && (unicode == L'\n' && previous_char != L'\n'))
    {
        // std::cout << "UNDERLINED!\n";
        force_add_underline();
        underline_start = 0;
    }

    // If we're using the strike through style and there's a new line, draw a line across all characters
    if (is_striketrough && (unicode == L'\n' && previous_char != L'\n'))
    {
        // std::cout << "STRIKETROUGH!\n";
        force_add_striketrough();
        striketrough_start = 0;
    }

    previous_char = unicode;

    // Handle special characters
    if ((unicode == L' ') || (unicode == L'\n') || (unicode == L'\t'))
    {
        // std::cout << "WHITESPACE!\n";
        // Update the current bounds (min coordinates)
        min_x = std::min(min_x, x);
        min_y = std::min(min_y, y);

        switch (unicode)
        {
            case L' ':  x += whitespace_width;     break;
            case L'\t': x += whitespace_width * 4; break;
            case L'\n': {
                y += max_line_spacing_since_start_of_line_multiplied; 
                x = 0; 
                for(; vertex_indice_start_of_line < vertices.getVertexCount(); ++vertex_indice_start_of_line) {
                    vertices[vertex_indice_start_of_line].position.y += max_line_spacing_since_start_of_line_multiplied;
                }
                max_line_spacing_since_start_of_line = max_line_spacing_since_start_of_line_multiplied = 0.0f; 
                break;
            }
        }

        // Update the current bounds (max coordinates)
        max_x = std::max(max_x, x);
        max_y = std::max(max_y, y);

        // Next glyph, no need to create a quad for whitespaces
        return;
    }

    // Apply the outline
    if (outline_thickness != 0)
    {
        // std::cout << "OUTLINE!\n";
        auto const& glyph = font->getGlyph(unicode, character_size, is_bold, outline_thickness);

        float left   = glyph.bounds.left;
        float top    = glyph.bounds.top;
        float right  = glyph.bounds.left + glyph.bounds.width;
        float bottom = glyph.bounds.top  + glyph.bounds.height;

        // Add the outline glyph to the vertices
        add_glyph_quad(vertices, sf::Vector2f{ x, y }, outline_color, glyph, shear, outline_thickness);

        // Update the current bounds with the outlined glyph bounds
        min_x = std::min(min_x, x + left   - shear * bottom - outline_thickness);
        max_x = std::max(max_x, x + right  - shear * top    - outline_thickness);
        min_y = std::min(min_y, y + top    - outline_thickness);
        max_y = std::max(max_y, y + bottom - outline_thickness);
    }

    // std::cout << "GETGLYPH(" << unicode << ", " << character_size << ", " << is_bold << ")\n";
    // Extract the current glyph's description
    auto const& glyph = font->getGlyph(unicode, character_size, is_bold);

    // std::cout << "ADDGLYPHQUAD(" << x << ", " << y << ", " << (int)fill_color.r << ", " << (int)fill_color.g << ", " << (int)fill_color.b << ", " << shear << ")\n";
    // Add the glyph to the vertices
    add_glyph_quad(vertices, sf::Vector2f{ x, y }, fill_color, glyph, shear);

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

}