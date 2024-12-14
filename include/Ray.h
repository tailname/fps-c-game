#pragma once
#include <SFML/Graphics.hpp>

class Ray {
private:
    sf::Vector3f origin;
    sf::Vector3f direction;
    float maxDistance;

public:
    Ray(const sf::Vector3f& origin, const sf::Vector3f& direction, float maxDistance = 1000.0f)
        : origin(origin), direction(direction), maxDistance(maxDistance) {
        // Normalize direction vector
        float length = std::sqrt(direction.x * direction.x + 
                               direction.y * direction.y + 
                               direction.z * direction.z);
        this->direction /= length;
    }

    sf::Vector3f getPoint(float distance) const {
        return origin + direction * distance;
    }

    const sf::Vector3f& getOrigin() const { return origin; }
    const sf::Vector3f& getDirection() const { return direction; }
    float getMaxDistance() const { return maxDistance; }
}; 