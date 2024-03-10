#include "bomb.h"

Bomb::Bomb(const sf::Vector2f position, float countdown, float explosionRadius, sf::Texture& texture)
    : m_countdown(countdown), m_explosionRadius(explosionRadius), m_exploded(false) {
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
    m_sprite.setScale(sf::Vector2f(0.05f, 0.05f));
}

void Bomb::Update(float deltaTime) {
    if(m_exploded) return;

    m_countdown -= deltaTime;
    if(m_countdown <= 0) {
        explode();
    }
}

void Bomb::Render(sf::RenderWindow& window) const {
    if (!m_exploded) {
        window.draw(m_sprite);
    }
}

bool Bomb::IsExploded() const {
    return m_exploded;
}

void Bomb::explode() {
    m_exploded = true;
}


