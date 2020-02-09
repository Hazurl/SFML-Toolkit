#pragma once

#include <utility>
#include <vector>

namespace sftk {

namespace interpolation {

using ratio_t = float;

template<typename T>
constexpr T linear(T const& start, T const& end, ratio_t ratio) noexcept {
    return start * (1 - ratio) + end * ratio;
}

template<typename T, T middle>
constexpr T quadratic(T const& start, T const& end, ratio_t ratio) noexcept {
    ratio_t opp = 1 - ratio;
    return 
        opp*opp * start
    +   2*opp*ratio * middle
    +   ratio*ratio * end;
}

template<typename T, T anchorA, T anchorB>
constexpr T cubic(T const& start, T const& end, ratio_t ratio) noexcept {
    ratio_t opp = 1 - ratio;
    return 
        opp*opp*opp * start
    +   3*opp*opp*ratio * anchorA
    +   3*opp*ratio*ratio * anchorB
    +   ratio*ratio*ratio * end;
}

template<typename T>
struct Bezier {

    Bezier(std::vector<T> _anchors) : anchors{ std::move(_anchors) } {}

    T operator()(T const& start, T const& end, ratio_t ratio) const noexcept {
        return interpolate(start, end, ratio, std::cbegin(anchors), std::cend(anchors));
    }

private:

    static T interpolate(T const& start, T const& end, ratio_t ratio, typename std::vector<T>::const_iterator first, typename std::vector<T>::const_iterator last) noexcept {
        std::size_t size = last - first;        
        if (size == 0) {
            return linear(start, end, ratio);    
        } else
        if (size == 1) {
            ratio_t opp = 1 - ratio;
            T middle = *first;
            return middle + (start - middle) * opp * opp + (end - middle) * ratio * ratio;
        } else
        if (size == 2) {
            ratio_t opp = 1 - ratio;
            T anchorA = *first;
            T anchorB = *++first;
            return 
                opp*opp*opp * start
            +   3*opp*opp*ratio * anchorA
            +   3*opp*ratio*ratio * anchorB
            +   ratio*ratio*ratio * end;
        }  
        return 
            (1 - ratio) * interpolate(start, *(last - 1), ratio, first, last - 1)
        +   ratio * interpolate(*first, end, ratio, first + 1, last);
    }

    std::vector<T> anchors;
};

template<typename T> Bezier(std::vector<T>) -> Bezier<T>;

template<typename T>
constexpr T delay_immediate(T const& start, T const& end, ratio_t ratio) noexcept {
    return start;
}

template<typename T>
constexpr T nearest(T const& start, T const& end, ratio_t ratio) noexcept {
    return ratio > static_cast<ratio_t>(0.5) ? end : start;
}

}

template<typename T, typename Interpolation = T(*)(T const&, T const&, interpolation::ratio_t)>
struct Animated {

    using time_t = float;
    using interpolation_t = Interpolation;

    template<typename...Args>
    explicit Animated(std::in_place_t, Args&&... args) noexcept
        : end(std::forward<Args>(args)...)
        , time{ 0 }
        , duration{ 0 } {}

    template<typename...Args>
    explicit Animated(interpolation_t interpolation_function, Args&&... args) noexcept
        : end(std::forward<Args>(args)...)
        , interp{ interpolation_function }
        , time{ 0 }
        , duration{ 0 } {}

    constexpr Animated& operator= (T value) noexcept {
        end = value;
        duration = 0;
        return *this;
    }

    constexpr void abord_animation() noexcept {
        end = start;
        duration = 0;
    }

    constexpr void stop_animation() noexcept {
        end = current();
        duration = 0;
    }

    constexpr void end_animation() noexcept {
        duration = 0;
    }

    constexpr time_t remaining() const noexcept {
        return std::max(duration - time, 0.0f);
    }

    constexpr T get_target() const noexcept {
        return end;
    }

    constexpr bool is_animated() const noexcept {
        return time < duration;
    }

    constexpr void update(time_t dt) noexcept {
        time += dt;
    }

    constexpr T current() const noexcept {
        return is_animated() ? interp(start, end, time / duration) : end;
    }

    constexpr operator T() const noexcept {
        return current();
    }

    constexpr void animate(T final_position, time_t animation_duration, interpolation_t interpolation_function) noexcept {
        animate(final_position, animation_duration);
        interp = std::move(interpolation_function);
    }

    constexpr void animate(T final_position, time_t animation_duration) noexcept {
        start = current();
        end = std::move(final_position);

        time = 0;
        duration = animation_duration;
    }

    constexpr void set_interpolation(interpolation_t interpolation_function) noexcept {
        start = current();
        duration -= time;
        time = 0;
        interp = interpolation_function;
    }

    constexpr interpolation_t const& get_interpolation() const noexcept {
        return interp;
    }

private:

    T start; 
    T end;
    interpolation_t interp;
    time_t time;
    time_t duration;

};

template<typename I, typename T> Animated(I&&, T&&) -> Animated<std::decay_t<T>, std::decay_t<I>>;
template<typename I, typename T> Animated(std::in_place_t, T&&) -> Animated<std::decay_t<T>>;


}