#pragma once

#include <SFML/Graphics.hpp>

#include <sftk/qol/QoL.hpp>
#include <sftk/print/Printer.hpp>

#include <cassert>
#include <cmath>

namespace sftk {

namespace details {

inline sf::Vector2f rotate_vector(sf::Vector2f const& v, float rad) {
    float cos_rad = std::cos(rad);
    float sin_rad = std::sin(rad);

    return sf::Vector2f{
        cos_rad * v.x - sin_rad * v.y,
        sin_rad * v.x + cos_rad * v.y
    };
}

inline sf::Vector2f rotate_point_around(sf::Vector2f const& v, sf::Vector2f const& o, float rad) {
    return o + rotate_vector(v - o, rad);
}




constexpr float pi = 3.14159265359f;
constexpr float deg_to_rad = (2.f * pi) / 360.f;


}

struct GizmoProperties {
    sf::RenderTarget* target;
    sf::Color color = sf::Color::Green;
    unsigned character_size = 20;
    bool draw_origin = true;
    sf::Font font;


    GizmoProperties& set_target(sf::RenderTarget& target_) {
        target = &target_;
        return *this;
    }

    GizmoProperties& set_color(sf::Color color_) {
        color = color_;
        return *this;
    }


    GizmoProperties& set_character_size(unsigned character_size_) {
        character_size = character_size_;
        return *this;
    }


    GizmoProperties& set_draw_origin(bool draw_origin_ = true) {
        draw_origin = draw_origin_;
        return *this;
    }


    GizmoProperties& set_font(sf::Font font_) {
        font = font_;
        return *this;
    }






    inline GizmoProperties& draw_rect(sf::IntRect const& rect, float rotation_deg = 0) {
        auto size = cast<float>(get_size(rect));
        auto top_left = cast<float>(get_position(rect));
        auto top_right = top_left + sf::Vector2f{ size.x, 0.f };
        auto bottom_left = top_left + sf::Vector2f{ 0.f, size.y };
        auto bottom_right = top_left + size;
        auto origin = top_left + size / 2.f;

        sf::Vertex top_left_vertex(details::rotate_point_around(top_left, origin, rotation_deg * details::deg_to_rad), color);

        std::array vertices {
            top_left_vertex,
            sf::Vertex(details::rotate_point_around(top_right, origin, rotation_deg * details::deg_to_rad), color),
            sf::Vertex(details::rotate_point_around(bottom_right, origin, rotation_deg * details::deg_to_rad), color),
            sf::Vertex(details::rotate_point_around(bottom_left, origin, rotation_deg * details::deg_to_rad), color),
            top_left_vertex
        };

        assert(target);
        target->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);

        if (draw_origin) {
            draw_point(cast<int>(origin));
        }

        return *this;
    }

    inline GizmoProperties& draw_point(sf::Vector2i const& point) {
        std::array vertices {
            sf::Vertex(cast<float>(point + sf::Vector2i{ -2, -2 }), color),
            sf::Vertex(cast<float>(point + sf::Vector2i{ -2, +2 }), color),
            sf::Vertex(cast<float>(point + sf::Vector2i{ +2, -2 }), color),
            sf::Vertex(cast<float>(point + sf::Vector2i{ +2, +2 }), color)
        };

        assert(target);
        target->draw(vertices.data(), vertices.size(), sf::PrimitiveType::TriangleStrip);

        return *this;
    }

    inline GizmoProperties& draw_circle(sf::Vector2i const& center, float radius) {
        auto pos = cast<float>(center);

        std::array<sf::Vertex, 31> vertices;
        for(std::size_t i = 0; i < vertices.size() - 1; ++i) {
            float angle = (static_cast<float>(i) / static_cast<float>(vertices.size() - 1)) * (2.f * details::pi);
            vertices[i] = sf::Vertex(pos + sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius), color);
        }

        vertices.back() = vertices[0];

        assert(target);
        target->draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);

        if (draw_origin) {
            draw_point(center);
        }

        return *this;
    }

    inline GizmoProperties& draw_arc(sf::Vector2i const& center, float radius, float start_deg, float end_deg) {
        float start_rad = std::clamp(start_deg, 0.f, 360.f) * details::deg_to_rad;
        float end_rad = std::clamp(end_deg, 0.f, 360.f) * details::deg_to_rad;

        if (end_rad <= start_rad) {
            end_rad += 2.f * details::pi;
        }

        auto pos = cast<float>(center);

        std::array<sf::Vertex, 31> vertices;
        auto vertices_count = static_cast<std::size_t>((end_rad - start_rad) / (2.f * details::pi) * 28.f + 3.f); 

        for(std::size_t i = 0; i < vertices_count; ++i) {
            float angle = (static_cast<float>(i) / static_cast<float>(vertices_count - 1)) * (end_rad - start_rad) + start_rad;
            vertices[i] = sf::Vertex(pos + sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius), color);
        }

        assert(target);
        target->draw(vertices.data(), vertices_count, sf::PrimitiveType::LineStrip);

        if (draw_origin) {
            draw_point(center);
        }

        return *this;
    }

    inline GizmoProperties& draw_closed_arc(sf::Vector2i const& center, float radius, float start_deg, float end_deg) {
        float start_rad = std::clamp(start_deg, 0.f, 360.f) * details::deg_to_rad;
        float end_rad = std::clamp(end_deg, 0.f, 360.f) * details::deg_to_rad;

        if (end_rad <= start_rad) {
            end_rad += 2.f * details::pi;
        }

        auto pos = cast<float>(center);

        std::array<sf::Vertex, 33> vertices;
        auto vertices_count = static_cast<std::size_t>((end_rad - start_rad) / (2.f * details::pi) * 28.f + 3.f); 

        for(std::size_t i = 0; i < vertices_count; ++i) {
            float angle = (static_cast<float>(i) / static_cast<float>(vertices_count - 1)) * (end_rad - start_rad) + start_rad;
            vertices[i] = sf::Vertex(pos + sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius), color);
        }

        vertices[vertices_count + 0] = sf::Vertex(pos, color);
        vertices[vertices_count + 1] = sf::Vertex(vertices[0].position, color);

        assert(target);
        target->draw(vertices.data(), vertices_count + 2, sf::PrimitiveType::LineStrip);

        if (draw_origin) {
            draw_point(center);
        }

        return *this;
    }

    inline GizmoProperties& draw_line(sf::Vector2i const& start, sf::Vector2i const& end) {
        std::array vertices {
            sf::Vertex(cast<float>(start), color),
            sf::Vertex(cast<float>(end), color)
        };

        assert(target);
        target->draw(vertices.data(), vertices.size(), sf::PrimitiveType::Lines);

        if (draw_origin) {
            draw_point(start);
        }

        return *this;
    }

    inline GizmoProperties& draw_arrow(sf::Vector2i const& start, sf::Vector2i const& end) {
        auto start_f = cast<float>(start);
        auto end_f = cast<float>(end);

        auto dir_1 = details::rotate_vector(end_f - start_f, 2.35619449019f /* 135 deg */);
        dir_1 *= 8.f / std::sqrt(dir_1.x * dir_1.x + dir_1.y * dir_1.y);
        auto line_1 = dir_1 + end_f;

        auto dir_2 = details::rotate_vector(end_f - start_f, 3.92699081699f /* 225 deg */);
        dir_2 *= 8.f / std::sqrt(dir_2.x * dir_2.x + dir_2.y * dir_2.y);
        auto line_2 = dir_2 + end_f;

        std::array vertices {
            sf::Vertex(start_f, color),
            sf::Vertex(end_f, color),
            sf::Vertex(end_f, color),
            sf::Vertex(line_1, color),
            sf::Vertex(end_f, color),
            sf::Vertex(line_2, color),
        };

        assert(target);
        target->draw(vertices.data(), vertices.size(), sf::PrimitiveType::Lines);

        if (draw_origin) {
            draw_point(start);
        }

        return *this;
    }

    inline GizmoProperties& draw_text(sf::Vector2i const& origin, sf::String const& str) {
        sf::Text text(str, font, character_size);
        text.setFillColor(color);
        text.setPosition(cast<float>(origin));

        assert(target);
        target->draw(text);

        if (draw_origin) {
            draw_point(origin);
        }

        return *this;
    }

};

#ifdef SFTK_GIZMO_GLOBAL_PROPERTIES

    inline GizmoProperties gizmo;

    inline GizmoProperties& draw_rect(sf::IntRect const& rect, float rotation_deg = 0) {
        return gizmo.draw_rect(rect, rotation_deg);
    }

    inline GizmoProperties& draw_point(sf::Vector2i const& point) {
        return gizmo.draw_point(point);
    }

    inline GizmoProperties& draw_circle(sf::Vector2i const& center, float radius) {
        return gizmo.draw_circle(center, radius);
    }

    inline GizmoProperties& draw_arc(sf::Vector2i const& center, float radius, float start_deg, float end_deg) {
        return gizmo.draw_arc(center, radius, start_deg, end_deg);
    }

    inline GizmoProperties& draw_closed_arc(sf::Vector2i const& center, float radius, float start_deg, float end_deg) {
        return gizmo.draw_closed_arc(center, radius, start_deg, end_deg);
    }

    inline GizmoProperties& draw_line(sf::Vector2i const& start, sf::Vector2i const& end) {
        return gizmo.draw_line(start, end);
    }

    inline GizmoProperties& draw_arrow(sf::Vector2i const& start, sf::Vector2i const& end) {
        return gizmo.draw_arrow(start, end);
    }

    inline GizmoProperties& draw_text(sf::Vector2i const& origin, sf::String const& str) {
        return gizmo.draw_text(origin, str);
    }


#endif

}