#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Map {
public:
    static constexpr int TILE_SIZE = 64;
    static constexpr int MAP_WIDTH = 24;
    static constexpr int MAP_HEIGHT = 24;

private:
    std::vector<std::vector<int>> grid;

public:
    Map() : grid(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, 0)) {
        // Initialize with a basic test map (1 represents walls)
        for(int i = 0; i < MAP_WIDTH; i++) {
            grid[0][i] = 1;  // Top wall
            grid[MAP_HEIGHT-1][i] = 1;  // Bottom wall
            grid[i][0] = 1;  // Left wall
            grid[i][MAP_WIDTH-1] = 1;  // Right wall
        }
        
        // Add some test walls
        grid[5][5] = 1;
        grid[5][6] = 1;
        grid[5][7] = 1;
    }

    bool isWall(int x, int y) const {
        if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
            return true;
        return grid[y][x] == 1;
    }

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape wall(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        wall.setFillColor(sf::Color(100, 100, 100));

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (grid[y][x] == 1) {
                    wall.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    window.draw(wall);
                }
            }
        }
    }
}; 