#include "../include/TileMap.h"


TileMap::TileMap() = default;
TileMap::~TileMap() = default;

bool TileMap::loadFromTileset(const std::string& tileset_path,
    sf::Vector2i tileSize,
    sf::Vector2i mapSize) {
    if (!tileset_.loadFromFile(tileset_path)) {
        std::cerr << "Failed to load tileset: " << tileset_path << std::endl;
        return false;
    }

    tileSize_ = tileSize;
    mapSize_ = mapSize;

    // Create tile rectangles
    int columns = tileset_.getSize().x / tileSize.x;
    int rows = tileset_.getSize().y / tileSize.y;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            tileRects_.emplace_back(
                x * tileSize.x,
                y * tileSize.y,
                tileSize.x,
                tileSize.y
            );
        }
    }

    return true;
}

void TileMap::addLayer(const std::vector<int>& tileIndices, int opacity) {
    Layer layer;
    layer.opacity = opacity;

    int x = 0;
    int y = 0;

    for (int gid : tileIndices) {
        if (gid > 0) {
            sf::Sprite sprite;
            sprite.setTexture(tileset_);
            sprite.setTextureRect(tileRects_[gid - 1]);
            sprite.setPosition(x * tileSize_.x, y * tileSize_.y);
            sprite.setColor(sf::Color(255, 255, 255, opacity));
            layer.tiles.push_back(sprite);
        }

        ++x;
        if (x >= mapSize_.x) {
            x = 0;
            ++y;
        }
    }

    layers_.push_back(std::move(layer));
}

void TileMap::render(sf::RenderWindow& window) {
    for (const auto& layer : layers_) {
        for (const auto& tile : layer.tiles) {
            window.draw(tile);
        }
    }
}
