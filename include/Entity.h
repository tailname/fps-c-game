#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include <filesystem>
#include <memory>
#include <unordered_map>
#include <bits/fs_path.h>

using std::shared_ptr;
using path = std::filesystem::path;

class Entity {
public:
    explicit Entity(const std::unordered_map<std::string, path>& texturePaths);
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void move(float deltaX, float deltaY) = 0;
    virtual void shoot() = 0;
    virtual void onCollision(Entity& other) = 0;

    void setPosition(const sf::Vector2f& pos);
    void createBody(b2World& world, const b2BodyDef& bodyDef);
    shared_ptr<b2Body> getBody();

protected:
    sf::Sprite mSprite;
    shared_ptr<b2Body> mBody;
    std::unordered_map<std::string, sf::Texture> m_textures; // map текстур
};