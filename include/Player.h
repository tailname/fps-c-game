#pragma once
#include "Entity.h"

#include<unordered_map>


class Player : public Entity {
public:
    Player();

    void move(float deltaX, float deltaY) override;
    void shoot() override;
    void onCollision(Entity &other) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void jump();
    void moveLeft();
    void moveRight();
    shared_ptr<b2BodyDef> getBodyDef() const;

private:
    float m_moveSpeed{ 1.5f };
    float m_jumpForce{ 15.0f };
    bool m_isOnGround{ true };
    b2BodyDef bodyDef;

    static inline const std::unordered_map<std::string, path> texturePaths = {
        {"idle", path("Image/main-character/Idle.gif")},
    };
};