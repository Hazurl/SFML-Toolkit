#pragma once

#include <utility>
#include <vector>

namespace sftk {

namespace interpolation {

using ratio_t = float;

template<typename T>
T linear(T const& start, T const& end, ratio_t ratio) {
    return start * (1 - ratio) + end * ratio;
}

template<typename T, T middle>
T quadratic(T const& start, T const& end, ratio_t ratio) {
    ratio_t opp = 1 - ratio;
    return middle + (start - middle) * opp * opp + (end - middle) * ratio * ratio;
}

template<typename T, T anchorA, T anchorB>
T cubic(T const& start, T const& end, ratio_t ratio) {
    ratio_t opp = 1 - ratio;
    return 
        opp*opp*opp * start
    +   3*opp*opp*ratio * anchorA
    +   3*opp*ratio*ratio * anchorB
    +   ratio*ratio*ratio * end;
}

template<typename T>
struct Bezier {
    template<typename...Ts>
    Bezier(Ts...anchors) : anchors{ anchors... } {}

    T operator()(T const& start, T const& end, ratio_t ratio) const {
        return interpolate(start, end, ratio, std::cbegin(anchors), std::cend(anchors));
    }

private:

    static T interpolate(T const& start, T const& end, ratio_t ratio, typename std::vector<T>::const_iterator first, typename std::vector<T>::const_iterator last) {
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

template<typename T>
T nothing(T const& start, T const& end, ratio_t ratio) {
    return start;
}

template<typename T>
T nearest(T const& start, T const& end, ratio_t ratio) {
    return ratio > static_cast<ratio_t>(0.5) ? end : start;
}

}

template<typename T, typename Interpolation = T(*)(T const&, T const&, interpolation::ratio_t)>
struct Animated {

    using time_t = float;
    using interpolation_t = Interpolation;

    template<typename...Args>
    Animated(Args&&... args) 
        : end(std::forward<Args>(args)...)
        , time{ 0 }
        , duration{ 0 } {}

    Animated& operator= (T value) {
        end = value;
        duration = 0;
        return *this;
    }

    bool is_animated() const {
        return time < duration;
    }

    void update(time_t dt) {
        time += dt;
    }

    T current() const {
        return is_animated() ? interp(start, end, time / duration) : end;
    }

    void animate(T final_position, time_t animation_duration, interpolation_t interpolation_function) {
        interp = interpolation_function;

        return animate(final_position, animation_duration);
    }

    inline void animate(T final_position, time_t animation_duration) {
        start = end;
        end = final_position;

        time = 0;
        duration = animation_duration;
    }

    void set_interpolation(interpolation_t interpolation_function) {
        interp = interpolation_function;
    }

private:

    T start; 
    T end;
    interpolation_t interp;
    time_t time;
    time_t duration;

};

}