//
// Created by ilya on 12/16/24.
//

#pragma once
#include <SFML/Graphics.hpp>

class Background {
public:
    Background(float windowWidth, float windowHeight) {
        sky.setSize(sf::Vector2f(windowWidth, windowHeight / 4 * 3));
        sky.setFillColor(sf::Color::Cyan);
        sky.setPosition(0.f, 0.f);

        floor.setSize(sf::Vector2f(windowWidth, windowHeight / 4));
        floor.setFillColor(sf::Color(139, 69, 19));
        floor.setPosition(0.f, windowHeight * 3 / 4);
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(sky);
        window.draw(floor);
    }

private:
    sf::RectangleShape sky;
    sf::RectangleShape floor;
};
