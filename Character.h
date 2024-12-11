#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Character {
private:
    sf::Vector2f position;
    float angle;  // Angle in degrees
    float moveSpeed;
    float rotationSpeed;

public:
    Character(float x = 2.0f, float y = 2.0f)
        : position(x, y), angle(0.0f), 
          moveSpeed(2.5f), rotationSpeed(3.0f) {}

    void rotate(float delta) {
        angle += delta * rotationSpeed;
        while (angle >= 360.0f) angle -= 360.0f;
        while (angle < 0.0f) angle += 360.0f;
    }

    void move(float forward, float strafe) {
        float rad = angle * 3.14159f / 180.0f;
        
        // Forward/backward movement
        position.x += std::cos(rad) * forward * moveSpeed;
        position.y += std::sin(rad) * forward * moveSpeed;
        
        // Strafe movement
        float strafeRad = rad + 3.14159f/2.0f;
        position.x += std::cos(strafeRad) * strafe * moveSpeed;
        position.y += std::sin(strafeRad) * strafe * moveSpeed;
    }

    const sf::Vector2f& getPosition() const { return position; }
    float getAngle() const { return angle; }
};

