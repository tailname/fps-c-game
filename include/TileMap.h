#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include<iostream>

class TileMap {
public:
    struct Layer {
        std::vector<sf::Sprite> tiles;
        int opacity{ 255 };
    };

    TileMap();
    ~TileMap();

    bool loadFromTileset(const std::string& tileset_path,
        sf::Vector2i tileSize,
        sf::Vector2i mapSize);

    void addLayer(const std::vector<int>& tileIndices, int opacity = 255);
    void render(sf::RenderWindow& window);

    const sf::Texture* getTileset() const { return &tileset_; }

private:
    sf::Texture tileset_;
    std::vector<Layer> layers_;
    std::vector<sf::IntRect> tileRects_;
    sf::Vector2i tileSize_;
    sf::Vector2i mapSize_;
};

