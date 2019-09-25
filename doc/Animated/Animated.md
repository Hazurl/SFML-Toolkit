# Animated

This system provides a structure to transform a variable with respect to time. It is a header-only library.

**Summary**
- [Animated](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Animated/Animated.md#animated)
- [Interpolation](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Animated/Animated.md#interpolation)
- [Example](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Animated/Animated.md#example)

## Animated

`sftk::Animated<T, F>` is almost a drop-in replacement for `T`. It contains an operator= to set the value `T` and a conversion operator. 

### Start Animation

To start the animation one can call the method `sftk::Animated<t>::animate(T final_position, time_t animation_duration, interpolation_t interpolation_function)`. It will start the animation from the current position to `final_position` in `animation_duration`. `interpolation_function` is the transformer, the parameter is optional and if not provided, it will use the previous one.

### Interpolation Function

The transformer is of type `F`, by default `T(*)(T const&, T const&, sftk::interpolation::ratio_t)`. One can set it in the constructor, with `set_interpolation` or when one start an animation. `F` must be callable with the parameters `T const& start, T const& end, interpolation::ratio_t ratio` and must returns a `T`: the interpolated value in the range `[start, end]` given the `ratio`. 

One can access constant reference to the transformer in use with `get_interpolation()`.

### When it's animated

When an animation started the method `is_animated` returns true until the end. One don't need to wait for an animation to end to start a new one. And if the value is set with `operator=(T)` the animation is stopped.

To access the value, one may call `current` or use the implicit conversion (`operator T`). To set the value, one can just use the operator `=`.
One can also get the target value with `get_target()` and the remaining duration with `remaining()`. All of these methods are const-correct.

In case one wants to stop the animation, the class provide three ways: 
- `abord_animation()` will reset the animation to its starting value 
- `stop_animation()` will only discard the animation, leaving it to its current value
- `end_animation()` will set the value to its target

Finally, one needs to call the function `update(time_t dt)` to continue the animation. If it's not animated, calling it is not required.  

### Constructors

The class contains 2 constructors: `template<typename...Args> Animated(Args&&...args)` and `template<typename...Args> Animated(interpolation_t interpolation_function, Args&&...args)`. The `args` or passed to construct the value. And `interpolation_function` is the transformer. In the first constructor, the transformer is default constructed.

## Interpolation

For ease of use, the namespace `sftk::interpolation` contains few tranformer:
- `template<typename T> T delay_immediate(T const&, T const&, sftk::interpolation::ratio_t)`: Stay at the same value until the end of the duration
- `template<typename T> T nearest(T const&, T const&, sftk::interpolation::ratio_t)`: Returns the start value before 50% of the duration then returns the target
- `template<typename T> T linear(T const&, T const&, sftk::interpolation::ratio_t)`: Linear interpolation
- `template<typename T, T anchor> T quadratic(T const&, T const&, sftk::interpolation::ratio_t)`: Quadratic interpolation in respect to `anchor`
- `template<typename T, T anchorA, T anchorB> T linear(T const&, T const&, sftk::interpolation::ratio_t)`: Cubic interpolation in respect to both anchors
- `template<typename T> struct Bezier`: Bezier curve (generalization of Linear, Quadratic and Cubic). The constructor takes an `std::initializer_list` of `T` as anchors.

All of them requires `T` to supports `operator+(T, T)` and `operator*(interpolation::ratio_t)`.

Of course one can provide his one's transformer. It only needs to be callable with the parameters detailed [here](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Animated/Animated.md#interpolationfunction).

## Example

[Source](https://github.com/Hazurl/SFML-Toolkit/blob/master/src/example/animated.cpp)

```cpp
#include <SFML/Graphics.hpp>

#include <sftk/animated/Animated.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    using namespace sftk;

    /*
        Click in the windows to animate the balls towards one's mouse
        One of them use a linear animation 
        and the other follows a bezier curve with the center as the only anchor
    */

    float const radius = 10;

    sf::CircleShape linear_circle(20);
    linear_circle.setOrigin(radius, radius);
    linear_circle.setFillColor(sf::Color{ 0x7A, 0x77, 0xD9, 123 });

    sf::CircleShape bezier_circle(20);
    bezier_circle.setOrigin(radius, radius);
    bezier_circle.setFillColor(sf::Color{ 0xF2, 0x50, 0x5D, 123 });

    sf::Vector2f const initial_position{ 400, 300 };
    Animated<sf::Vector2f> linear_position(interpolation::linear<sf::Vector2f>, initial_position);
    Animated<sf::Vector2f, interpolation::Bezier<sf::Vector2f>> bezier_position(initial_position);
    linear_circle.setPosition(linear_position.current());
    bezier_circle.setPosition(bezier_position.current());

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f target{ static_cast<float>(event.mouseButton.x - radius), static_cast<float>(event.mouseButton.y  - radius) };

                linear_position.animate(target, 1);
                bezier_position.animate(target, 1, /* Bezier anchors */{ initial_position });
            }
        }

        auto dt = clock.restart().asSeconds();
        linear_position.update(dt);
        bezier_position.update(dt);
        linear_circle.setPosition(linear_position);
        bezier_circle.setPosition(bezier_position);

        window.clear();

        window.draw(linear_circle);
        window.draw(bezier_circle);

        window.display();
    }
}
```