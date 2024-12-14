#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Ray.h"

class Raycaster {
private:
    static constexpr float FOV = 60.0f;  // Field of view in degrees
    static constexpr int NUM_RAYS = 320;  // Number of rays to cast
    static constexpr float MAX_DEPTH = 16.0f;  // Maximum ray distance

    const Map& map;
    std::vector<float> depthBuffer;

public:
    Raycaster(const Map& map) : map(map), depthBuffer(NUM_RAYS) {}

    void castRays(const sf::Vector2f& position, float angle, sf::RenderWindow& window) {
        float rayAngle = angle - FOV / 2;
        const float angleStep = FOV / float(NUM_RAYS);
        const float columnWidth = WINDOW_WIDTH / float(NUM_RAYS);

        for (int i = 0; i < NUM_RAYS; i++) {
            float rad = rayAngle * 3.14159f / 180.0f;
            sf::Vector2f direction(std::cos(rad), std::sin(rad));
            
            float depth = castRay(position, direction);
            depthBuffer[i] = depth;

            // Calculate wall height
            float perpDistance = depth * std::cos((rayAngle - angle) * 3.14159f / 180.0f);
            float wallHeight = (Map::TILE_SIZE * WINDOW_HEIGHT) / perpDistance;
            
            // Draw wall strip
            sf::RectangleShape wall(sf::Vector2f(columnWidth + 1, wallHeight));
            wall.setPosition(i * columnWidth, (WINDOW_HEIGHT - wallHeight) / 2);
            
            // Shade walls based on distance
            int shade = static_cast<int>(255 * (1.0f - std::min(depth / MAX_DEPTH, 1.0f)));
            wall.setFillColor(sf::Color(shade, shade, shade));
            
            window.draw(wall);
            rayAngle += angleStep;
        }
    }

private:
    float castRay(const sf::Vector2f& position, const sf::Vector2f& direction) {
        sf::Vector2f rayPos = position;
        sf::Vector2f step(
            std::sqrt(1 + (direction.y / direction.x) * (direction.y / direction.x)),
            std::sqrt(1 + (direction.x / direction.y) * (direction.x / direction.y))
        );
        
        sf::Vector2i mapCheck(int(rayPos.x), int(rayPos.y));
        sf::Vector2f rayLength;
        sf::Vector2i stepDir;

        // Initialize ray length and step direction
        if (direction.x < 0) {
            stepDir.x = -1;
            rayLength.x = (rayPos.x - float(mapCheck.x)) * step.x;
        } else {
            stepDir.x = 1;
            rayLength.x = (float(mapCheck.x + 1) - rayPos.x) * step.x;
        }
        
        if (direction.y < 0) {
            stepDir.y = -1;
            rayLength.y = (rayPos.y - float(mapCheck.y)) * step.y;
        } else {
            stepDir.y = 1;
            rayLength.y = (float(mapCheck.y + 1) - rayPos.y) * step.y;
        }

        float distance = 0.0f;
        while (distance < MAX_DEPTH) {
            // Walk along shortest ray length
            if (rayLength.x < rayLength.y) {
                mapCheck.x += stepDir.x;
                distance = rayLength.x;
                rayLength.x += step.x;
            } else {
                mapCheck.y += stepDir.y;
                distance = rayLength.y;
                rayLength.y += step.y;
            }

            // Check if ray has hit a wall
            if (map.isWall(mapCheck.x, mapCheck.y)) {
                return distance;
            }
        }
        
        return MAX_DEPTH;
    }
}; 