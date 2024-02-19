#include "playerManager.h"

PlayerManager::PlayerManager(const sf::Texture& texture) {
	m_player = std::make_unique<Player>(texture);
}

void PlayerManager::HandleInput(const float& deltaTime) const {
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		direction.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		direction.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		direction.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direction.x += 1;
	}

	m_player->Move(direction * deltaTime);
}

void PlayerManager::Update(const float& deltaTime) const {
	HandleInput(deltaTime);
	m_player->Update(deltaTime);
}

void PlayerManager::Render(sf::RenderWindow& renderWindow) const {
	m_player->Render(renderWindow);
}
