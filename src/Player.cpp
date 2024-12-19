#include "Player.h"

Player::Player() : Entity(texturePaths){
    bodyDef.type = b2_dynamicBody;          // Тип тела: динамическое
    bodyDef.position.Set(0.0f, 10.0f);      // Начальная позиция (x, y)
    bodyDef.angle = 0.0f;                   // Угол поворота в радианах
    bodyDef.fixedRotation = false;
}

void Player::move(float deltaX, float deltaY) {
    // Перемещение игрока на основе deltaX и deltaY
    mSprite.move(deltaX * m_moveSpeed, deltaY * m_moveSpeed);  // Перемещаем спрайт

    if (mBody) {
        b2Vec2 newPos(mSprite.getPosition().x, mSprite.getPosition().y);
        mBody->SetTransform(newPos, mBody->GetAngle());  // Перемещаем тело Box2D
    }
}

void Player::shoot() {
    // Логика для выстрела (например, создание снаряда)
    // Это просто пример, нужно будет добавить код для выстрела
    std::cout << "Player shoots!" << std::endl;
}

void Player::onCollision(Entity& other) {
    // Логика для обработки столкновений (например, с врагами или препятствиями)
    // Это просто пример, нужно будет добавить код для обработки коллизий
    std::cout << "Player collided with another entity!" << std::endl;
}

void Player::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        jump();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveRight();
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(mSprite);
}

void Player::jump() {
    if (m_isOnGround) {
        if (mBody) {
            mBody->ApplyForceToCenter(b2Vec2(0, m_jumpForce), true);
            m_isOnGround = false;
            std::cout << "Player jumped!" << std::endl;
        }
    }
}

void Player::moveLeft() {
    // Перемещаем игрока влево
    move(-1.0f, 0.0f);
    std::cout << "Player moving left!" << std::endl;
}

void Player::moveRight() {
    // Перемещаем игрока вправо
    move(1.0f, 0.0f);
}

shared_ptr<b2BodyDef> Player::getBodyDef() const {
    return std::make_shared<b2BodyDef>(bodyDef);
}
