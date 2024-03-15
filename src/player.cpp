#include "player.h"

constexpr float holdTime = 0.08f;

Player::Player(const sf::Texture& texture) {
	m_sprite.setTexture(texture);
	m_sprite.setScale(1.8f, 1.8f);
	m_sprite.setPosition(70.f, 53.f);
	AddAnimation(AnimationIndex::WalkingUp, 16, 0, 18,26, 3);
	AddAnimation(AnimationIndex::WalkingDown, 0, 26, 18,26, 3, false);
	AddAnimation(AnimationIndex::WalkingLeft, 18, 78, 18, 26, 3);
	AddAnimation(AnimationIndex::WalkingRight, 18, 26, 18, 26, 3);
	AddAnimation(AnimationIndex::IdleUp, 0, 0, 18, 26, 1, false);
	AddAnimation(AnimationIndex::IdleDown, 0, 52, 18, 26, 1, false);
	AddAnimation(AnimationIndex::IdleLeft, 18, 78, 18, 26, 1, false);
	AddAnimation(AnimationIndex::IdleRight, 18, 26, 18, 26, 1, false); // Note the change from IdleRigth to IdleRight for consistency
	AddAnimation(AnimationIndex::IdleDead, 49, 104, 18, 26, 1, false);
	AddAnimation(AnimationIndex::Dead, 49, 104, 18, 26, 3);
	// animations[static_cast<int>(AnimationIndex::WalkingUp)] = Animation(16, 0, 18,26, 3, holdTime);
	// animations[static_cast<int>(AnimationIndex::WalkingDown)] = Animation(0, 26, 18,26, 3, holdTime, false);
	// animations[static_cast<int>(AnimationIndex::WalkingLeft)] = Animation(18, 78, 18,26, 3, holdTime);
	// animations[static_cast<int>(AnimationIndex::WalkingRight)] = Animation(18, 26, 18,26, 3, holdTime);
	// animations[static_cast<int>(AnimationIndex::IdleDown)] = Animation(0, 52, 18, 26, 1, holdTime, false);
	// animations[static_cast<int>(AnimationIndex::IdleUp)] = Animation(0, 0, 18, 26, 1, holdTime, false);
	// animations[static_cast<int>(AnimationIndex::IdleLeft)] = Animation(18, 78, 18, 26, 1, holdTime, false);
	// animations[static_cast<int>(AnimationIndex::IdleRigth)] = Animation(18, 26, 18, 26, 1, holdTime, false);
	// animations[static_cast<int>(AnimationIndex::Dead)] = Animation(49, 104, 18, 26, 3, holdTime);
	// animations[static_cast<int>(AnimationIndex::IdleDead)] = Animation(49, 104, 18, 26, 1, holdTime, false);
	
}

void Player::Update(const float& deltaTime) {
	// TODO: set player behaviour

	if (m_died) {
		currentAnimation = m_speed != 0.f ? AnimationIndex::Dead : AnimationIndex::IdleDead;
		m_direction = sf::Vector2f(0.f, 0.f);
		m_speed = 0.f;
	}
	const auto& currentAnim = m_animations[static_cast<int>(currentAnimation)];
	currentAnim->Update(deltaTime);
	currentAnim->ApplyToSprite(m_sprite);
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
				currentAnimation = AnimationIndex::IdleRight;
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

void Player::AddAnimation(AnimationIndex index, int x, int y, int width, int height, int nFrames,
	bool row) {
	m_animations.emplace_back(std::make_unique<Animation>(x, y, width, height, nFrames, holdTime, row));
}

