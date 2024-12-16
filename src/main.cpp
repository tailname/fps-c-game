#include <SFML/Graphics.hpp>

#include "Background.h"

constexpr float WINDOW_HEIGHT = 720.0;
constexpr float WINDOW_WIDTH  = 1280.0;
int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FPS Roguelike");
    Background background(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (window.isOpen())
    {
        window.clear();
        background.draw(window);
        window.display();
        sf::Event event{};//создаём пустой евент, чтобы ниже в цикле в него передавть события
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }

    return 0;
}