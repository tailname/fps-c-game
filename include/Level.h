#pragma once
#include<iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include <map>
#include "TileMap.h"
#include "../xml_parser/src/tinyxml2.h"


class Level {
public:
    struct ObjectData {
        std::string name;
        std::string type;
        sf::FloatRect bounds;
        sf::Sprite sprite;
        std::map<std::string, std::string> properties;

        template<typename T>
        T getProperty(const std::string& name) const;
    };

public:
    Level();
    ~Level();

    bool loadFromFile(const std::string& filename, b2World& world);
    void render(sf::RenderWindow& window);

    const ObjectData* getObject(const std::string& name) const;
    std::vector<const ObjectData*> getObjects(const std::string& name) const;
    sf::Vector2i getTileSize() const { return tileSize_; }

    void setScale(float scaleX, float scaleY);
    void update(float deltaTime);
    void cleanupMarkedObjects();

private:
    void createPhysicsBody(const ObjectData& obj, b2World& world, b2BodyType bodyType);
    void loadTilesets(const tinyxml2::XMLElement* mapNode);
    void loadLayers(const tinyxml2::XMLElement* mapNode);
    void loadObjects(const tinyxml2::XMLElement* mapNode);

private:
    std::unique_ptr<TileMap> tileMap_;
    std::vector<ObjectData> objects_;
    std::vector<b2Body*> m_bodies;
    sf::Vector2i tileSize_;
    sf::Vector2i mapSize_;
};