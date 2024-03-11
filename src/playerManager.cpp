#include "playerManager.h"

#include <iostream>

PlayerManager::PlayerManager(const sf::Texture& playerTexture, const sf::Texture& bombTexture)
	: m_bombTexture(bombTexture) {
	m_player = std::make_unique<Player>(playerTexture);
}

void PlayerManager::HandleInput(const float& deltaTime) {
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

	const sf::Vector2f newPosition = m_player->GetPosition() + direction * m_player->GetSpeed() * deltaTime;

	const sf::FloatRect newBounds(newPosition, m_player->GetSize());
	if (!isCollidingWithBombs(newPosition, newBounds)) {
		m_player->Move(direction * deltaTime);
	}
	
	// Place bombs
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		PlaceBomb();
	}
}

void PlayerManager::Update(const float& deltaTime) {
	HandleInput(deltaTime);
	m_player->Update(deltaTime);

	for (auto& bomb : m_bombs) {
		bomb.Update(deltaTime);
	}

	m_bombs.erase(std::remove_if(m_bombs.begin(), m_bombs.end(), [](const Bomb& b){return b.IsExploded(); }), m_bombs.end());
}

void PlayerManager::Render(sf::RenderWindow& renderWindow) const {
	m_player->Render(renderWindow);

	for (auto& bomb : m_bombs) {
		bomb.Render(renderWindow);
	}
}

void PlayerManager::PlaceBomb() {
	// get position of player and spawn bomb
	const float offsetDistance = 0.5;
	const sf::Vector2f position = m_player->GetPosition();
	const sf::Vector2f direction = m_player->GetDirection();
	sf::Vector2f positionOffset = position + direction * offsetDistance;
	m_bombs.emplace_back(positionOffset, 3.0f, 100.0f, m_bombTexture);
}

bool PlayerManager::isCollidingWithBombs(const sf::Vector2f& newPosition, const sf::FloatRect& playerBounds) {
	for (const auto& bomb: m_bombs) {
		if(bomb.GetGlobalBounds().intersects(playerBounds)) {
			return true;
		}
	}
	return false;
}

