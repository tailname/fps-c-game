#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>

class Entity {
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;

    void createBody(b2World& world, const b2BodyDef& bodyDef);
    b2Body* getBody() { return m_body; }

protected:
    sf::Sprite m_sprite;
    b2Body* m_body{ nullptr };
};