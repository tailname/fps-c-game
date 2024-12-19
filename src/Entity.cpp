#include "../include/Entity.h"

Entity::Entity(const std::unordered_map<std::string, path>& texturePaths) {
    for (const auto&[name, path] : texturePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path.string())) {
            throw std::runtime_error("Failed to load texture from " + path.string());
        }
        m_textures[name] = texture;
    }
    if (!m_textures.empty()) {
        mSprite.setTexture(m_textures.begin()->second);
    }
}

void Entity::setPosition(const sf::Vector2f& pos) {
    mSprite.setPosition(pos);  // Óñòàíàâëèâàåì ïîçèöèþ ñïðàéòà
    if (mBody) {
        mBody->SetTransform(b2Vec2(pos.x, pos.y), mBody->GetAngle());  // Óñòàíàâëèâàåì ïîçèöèþ òåëà Box2D (åñëè îíî ñóùåñòâóåò)
    }
}

void Entity::createBody(b2World& world, const b2BodyDef& bodyDef) {
    mBody = shared_ptr<b2Body>(world.CreateBody(&bodyDef), [&world](b2Body* body) {
        world.DestroyBody(body);  // Óäàëÿåì òåëî ïðè ðàçðóøåíèè ñóùíîñòè
    });
}
shared_ptr<b2Body> Entity::getBody() {
    return mBody;
}
