#include <SFML/Graphics.hpp>

#include <sftk/ressource/Ressource.hpp>

#include <iostream>

int main() {
/*
    using sftk::operator<<;

    std::cout << sf::Vector2f(42.42f, 1337) << '\n';
    std::cout << sf::Vector2i(42, -1337) << '\n';
    std::cout << sf::Vector2u(42, 1337) << '\n';

    std::cout << [] () { auto s = sf::CircleShape(12); s.setPosition({10, -20}); return s; }() << '\n';
*/


    auto load = sftk::backup( // backup execute the first loader, if it fail it execute the second one
        sftk::load_from_file<sf::Texture>("non_existing_file.wtf"),
        sftk::load_from_file<sf::Texture>("../brick-breaker/res/img/bw_brick_soft.png")
    );

    sftk::Ressource<sf::Texture> res(load);
    sf::Sprite s;
    auto t_ = res.get(); // if you delete this line, the texture will bed destroyed since the only reference to it will go out of scope
    // in order to not run into this behaviour, if you use a sprite (that need a reference to the texture), 
    // you must keep the handler returned by sftk::Ressource<T>::get
    {
        auto t = res.get();
        s.setTexture(*t);
    } // `t` goes out of scope, it it's the only handler on this ressource, it will unload it 

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        window.draw(s);
        window.display();
    }

}