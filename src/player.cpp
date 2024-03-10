#include "player.h"

Player::Player(const sf::Texture& texture) {
	m_sprite.setTexture(texture);
	m_sprite.setScale(sf::Vector2f(0.05f, 0.05f));
	m_sprite.setPosition(100.f, 100.f);
}


void Player::Update(const float& deltaTime) {
	// TODO: set player behaviour
}

void Player::Move(sf::Vector2f direction) {
	if(direction.x != 0.f || direction.y != 0.f) {
		const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length;
		m_lastDirection = direction;
	}
	m_sprite.move(direction * m_speed);
}

void Player::Render(sf::RenderWindow& renderWindow) const {
	renderWindow.draw(m_sprite);
}

sf::Vector2f Player::GetPosition() const {
	return m_sprite.getPosition();
}

sf::Vector2f Player::GetDirection() const {
	return m_lastDirection;
}
