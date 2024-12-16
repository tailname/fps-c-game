#include <SFML/Graphics.hpp>
#include "..//xml_parser/src/tinyxml2.h"
constexpr float WINDOW_HEIGHT = 720.0;
constexpr float WINDOW_WIDTH  = 1280.0;
int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FPS Roguelike");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}