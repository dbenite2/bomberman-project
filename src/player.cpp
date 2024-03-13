#include "player.h"


Player::Player(const sf::Texture& texture) {
	m_sprite.setTexture(texture);
	m_sprite.setScale(1.5f, 1.5f);
	m_sprite.setPosition(70.f, 53.f);
}


void Player::Update(const float& deltaTime) {
	// TODO: set player behaviour
	if(m_died) {
		m_sprite.rotate(90);
	}
}

void Player::Move(sf::Vector2f direction) {
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

float Player::GetSpeed() const {
	return m_speed;
}

sf::Vector2f Player::GetSize() const {
	return m_size;
}

sf::FloatRect Player::GetGlobalBounds() {
	return m_sprite.getGlobalBounds();
}

void Player::SetPosition(const sf::Vector2f& position) {
	m_sprite.setPosition(position);
}

void Player::SetDiedState(bool state) {
	m_died = state;
}

