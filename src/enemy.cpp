#include "enemy.h"

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position,const sf::Vector2f& initialDirection) : m_direction(initialDirection) {
    m_sprite.setTexture(texture);
    m_sprite.setScale(2.5f, 2.5f);
    m_sprite.setPosition(position);
    m_animation = new Animation(0,0,16,16,6, 0.08f);
}

void Enemy::Update(const float& deltaMS) {
    m_animation->Update(deltaMS);
    m_animation->ApplyToSprite(m_sprite);
    m_sprite.move(m_direction * m_speed * deltaMS);
}

void Enemy::SetState(bool state) {
    m_died = state;
}

bool Enemy::IsDead() const {
    return m_died;
}



void Enemy::Render(sf::RenderWindow& renderWindow) const {
    renderWindow.draw(m_sprite);
}

void Enemy::SetDirection(const sf::Vector2f& direction) {
    m_direction = direction;
}

sf::Vector2f Enemy::GetPosition() const {
    return m_sprite.getPosition();
}

void Enemy::SetPosition(const sf::Vector2f& position) {
    m_sprite.setPosition(position);
}

sf::Vector2f Enemy::GetDirection() const {
    return m_direction;
}

