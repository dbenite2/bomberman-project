#include "player.h"

#include <stdbool.h>

Player::Player(const sf::Texture& texture) {
	m_sprite.setTexture(texture);
	m_sprite.setScale(1.8f, 1.8f);
	m_sprite.setPosition(70.f, 53.f);
	animations[static_cast<int>(AnimationIndex::WalkingUp)] = Animation(16, 0, 18,26, true, true);
	animations[static_cast<int>(AnimationIndex::WalkingDown)] = Animation(0, 26, 18,26, false, true);
	animations[static_cast<int>(AnimationIndex::WalkingLeft)] = Animation(18, 78, 18,26, true, true);
	animations[static_cast<int>(AnimationIndex::WalkingRight)] = Animation(18, 26, 18,26, true, true);
	animations[static_cast<int>(AnimationIndex::IdleDown)] = Animation(0, 52, 18, 26, true, false);
	animations[static_cast<int>(AnimationIndex::IdleUp)] = Animation(0, 0, 18, 26, true, false);
	animations[static_cast<int>(AnimationIndex::IdleLeft)] = Animation(18, 78, 18, 26, true, false);
	animations[static_cast<int>(AnimationIndex::IdleRigth)] = Animation(18, 26, 18, 26, true, false);
	animations[static_cast<int>(AnimationIndex::Dead)] = Animation(49, 104, 18, 26, true, true);
	animations[static_cast<int>(AnimationIndex::IdleDead)] = Animation(49, 104, 18, 26, true, false);
	
}


void Player::Update(const float& deltaTime) {
	// TODO: set player behaviour
	if(m_died && m_speed != 0.f) {
		currentAnimation = AnimationIndex::Dead;
		m_direction = {0,0};
		m_speed = 0.f;
	}
	animations[int(currentAnimation)].Update(deltaTime);
	animations[int(currentAnimation)].ApplyToSprite(m_sprite);
	if (m_speed == 0.f) {
		currentAnimation = AnimationIndex::IdleDead;
	}
	Move(m_direction * m_speed * deltaTime);
}

void Player::Move(sf::Vector2f direction) {
	m_sprite.move(direction);
}

void Player::SetDirection(const sf::Vector2f& direction) {
	m_direction = direction;
	if (!m_died) {
		if (m_direction.x < 0.f) {
			currentAnimation = AnimationIndex::WalkingLeft;
			m_lastDirection = direction;
		} else if (m_direction.x > 0.f) {
			currentAnimation = AnimationIndex::WalkingRight;
			m_lastDirection = direction;
		} else if (m_direction.y < 0.f) {
			currentAnimation = AnimationIndex::WalkingUp;
			m_lastDirection = direction;
		} else if (m_direction.y > 0.f) {
			currentAnimation = AnimationIndex::WalkingDown;
			m_lastDirection = direction;
		} else if (m_direction.x == 0.f && m_direction.y == 0.f) {
			if (m_lastDirection.x < 0.f) {
				currentAnimation = AnimationIndex::IdleLeft;
			} else if (m_lastDirection.x > 0.f) {
				currentAnimation = AnimationIndex::IdleRigth;
			} else if (m_lastDirection.y < 0.f) {
				currentAnimation = AnimationIndex::IdleUp;
			} else if (m_lastDirection.y > 0.f) {
				currentAnimation = AnimationIndex::IdleDown;
			}
		}
	}
}



void Player::Render(sf::RenderWindow& renderWindow) const {
	if (!m_died) {
	}
	renderWindow.draw(m_sprite);
}

sf::Vector2f Player::GetPosition() const {
	return m_sprite.getPosition();
}

sf::Vector2f Player::GetDirection() const {
	return m_direction;
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

