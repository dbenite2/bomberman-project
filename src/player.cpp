#include "player.h"


Player::Player(const sf::Texture& texture) {
	m_sprite.setTexture(texture);
	m_sprite.setScale(m_size);
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

	sf::Vector2f newPosition = m_sprite.getPosition() + direction * m_speed;

	const float leftBoundary = 0.f;
	const float rightBoundary = 800.f;
	const float topBoundary = 0.f;
	const float bottomBoundary = 600.f;

	if (newPosition.x < leftBoundary) {
		newPosition.x = leftBoundary;
	} else if (newPosition.x + m_sprite.getGlobalBounds().width > rightBoundary) {
		newPosition.x = rightBoundary - m_sprite.getGlobalBounds().width;
	}

	if (newPosition.y < topBoundary) {
		newPosition.y = topBoundary;
	} else if (newPosition.y + m_sprite.getGlobalBounds().height > bottomBoundary) {
		newPosition.y = bottomBoundary - m_sprite.getGlobalBounds().height;
	}
	
	// m_sprite.move(direction * m_speed);
	m_sprite.setPosition(newPosition);
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


