#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    Player();

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void handleInput();
    void jump();
    void moveLeft();
    void moveRight();
    void stop();

private:
    float m_moveSpeed{ 5.0f };
    float m_jumpForce{ 15.0f };
    bool m_isOnGround{ false };
};