#include "../include/Level.h"
#include <iostream>

using namespace tinyxml2;

Level::Level() = default;
Level::~Level() = default;

bool Level::loadFromFile(const std::string& filename, b2World& world) {
    XMLDocument doc;
    
    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load level file: " << filename << std::endl;
        return false;
    }

    auto* mapNode = doc.FirstChildElement("map");
    if (!mapNode) {
        std::cerr << "Map node not found" << std::endl;
        return false;
    }

    // Load map dimensions
    mapSize_.x = mapNode->IntAttribute("width");
    mapSize_.y = mapNode->IntAttribute("height");
    tileSize_.x = mapNode->IntAttribute("tilewidth");
    tileSize_.y = mapNode->IntAttribute("tileheight");

    // Initialize systems
    tileMap_ = std::make_unique<TileMap>();

    try {
        loadTilesets(mapNode);
        loadLayers(mapNode);
        loadObjects(mapNode);

        // Create physics bodies for static objects
        for (const auto& obj : objects_) {
            if (obj.type == "block") {
                createPhysicsBody(obj, world, b2_staticBody);
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading level: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void Level::loadTilesets(const XMLElement* mapNode) {
    auto* tilesetElem = mapNode->FirstChildElement("tileset");
    if (!tilesetElem) {
        throw std::runtime_error("No tileset found in map");
    }

    auto* imageElem = tilesetElem->FirstChildElement("image");
    if (!imageElem) {
        throw std::runtime_error("No image found in tileset");
    }

    const char* imagePath = imageElem->Attribute("source");
    if (!imagePath || !tileMap_->loadFromTileset(imagePath, tileSize_, mapSize_)) {
        throw std::runtime_error("Failed to load tileset image");
    }
}

void Level::loadLayers(const XMLElement* mapNode) {
    for (auto* layerElem = mapNode->FirstChildElement("layer");
        layerElem;
        layerElem = layerElem->NextSiblingElement("layer")) {

        int opacity = 255;
        float opacityFloat;
        if (layerElem->QueryFloatAttribute("opacity", &opacityFloat) == XML_SUCCESS) {
            opacity = static_cast<int>(255.0f * opacityFloat);
        }

        auto* dataElem = layerElem->FirstChildElement("data");
        if (!dataElem) continue;

        std::vector<int> tileIndices;
        for (auto* tileElem = dataElem->FirstChildElement("tile");
            tileElem;
            tileElem = tileElem->NextSiblingElement("tile")) {

            tileIndices.push_back(tileElem->IntAttribute("gid"));
        }

        tileMap_->addLayer(tileIndices, opacity);
    }
}

void Level::loadObjects(const XMLElement* mapNode) {
    for (auto* groupElem = mapNode->FirstChildElement("objectgroup");
        groupElem;
        groupElem = groupElem->NextSiblingElement("objectgroup")) {

        for (auto* objElem = groupElem->FirstChildElement("object");
            objElem;
            objElem = objElem->NextSiblingElement("object")) {

            ObjectData obj;
            obj.name = objElem->Attribute("name") ? objElem->Attribute("name") : "";
            obj.type = objElem->Attribute("type") ? objElem->Attribute("type") : "";

            float x = objElem->FloatAttribute("x");
            float y = objElem->FloatAttribute("y");
            float w = objElem->FloatAttribute("width", tileSize_.x);
            float h = objElem->FloatAttribute("height", tileSize_.y);

            obj.bounds = sf::FloatRect(x, y, w, h);

            // Load sprite if there's a gid (tile reference)
            if (int gid = objElem->IntAttribute("gid", 0)) {
                // Get the tileset texture from TileMap
                const sf::Texture* tilesetTexture = tileMap_->getTileset();
                if (tilesetTexture) {
                    obj.sprite.setTexture(*tilesetTexture);
                    
                    // Calculate texture coordinates based on gid
                    int tilesetWidth = tilesetTexture->getSize().x / tileSize_.x;
                    int tileId = gid - 1; // GIDs are 1-based
                    
                    int tu = tileId % tilesetWidth;
                    int tv = tileId / tilesetWidth;
                    
                    // Set the texture rectangle for the sprite
                    obj.sprite.setTextureRect(sf::IntRect(
                        tu * tileSize_.x,
                        tv * tileSize_.y,
                        tileSize_.x,
                        tileSize_.y
                    ));
                    
                    // Set position and size
                    obj.sprite.setPosition(x, y - h);
                    float scaleX = w / tileSize_.x;
                    float scaleY = h / tileSize_.y;
                    obj.sprite.setScale(scaleX, scaleY);
                }
            }

            // Load properties
            if (auto* propsElem = objElem->FirstChildElement("properties")) {
                for (auto* propElem = propsElem->FirstChildElement("property");
                    propElem;
                    propElem = propElem->NextSiblingElement("property")) {

                    const char* name = propElem->Attribute("name");
                    const char* value = propElem->Attribute("value");
                    if (name && value) {
                        obj.properties[name] = value;
                    }
                }
            }

            objects_.push_back(obj);
        }
    }
}



void Level::createPhysicsBody(const ObjectData& obj, b2World& world, b2BodyType bodyType) {
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(
        obj.bounds.left + obj.bounds.width / 2.0f,
        obj.bounds.top + obj.bounds.height / 2.0f
    );
    bodyDef.fixedRotation = true;

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(obj.bounds.width / 2.0f, obj.bounds.height / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    m_bodies.push_back(body);
}

void Level::render(sf::RenderWindow& window) {
    tileMap_->render(window);

    // Render objects with sprites
    for (const auto& obj : objects_) {
        if (obj.sprite.getTexture() != nullptr) {
            window.draw(obj.sprite);
        }
    }
}

const Level::ObjectData* Level::getObject(const std::string& name) const {
    auto it = std::find_if(objects_.begin(), objects_.end(),
        [&name](const ObjectData& obj) { return obj.name == name; });
	if (it == objects_.end()) 
    {
        return nullptr;
    }
    return &(*it);
}

std::vector<const Level::ObjectData*> Level::getObjects(const std::string& name) const {
    std::vector<const ObjectData*> result;
    for (const auto& obj : objects_) {
        if (obj.name == name) {
            result.push_back(&obj);
        }
    }
    return result;
}