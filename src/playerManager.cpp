#include "playerManager.h"

// add to constructor

PlayerManager::PlayerManager(const sf::Texture& playerTexture, const sf::Texture& bombTexture,
	const sf::Texture& explosionTexture, SceneManager* sceneManager, const float& playerSpeed,
	const sf::Vector2f& playerPosition, const sf::Vector2f& playerSpriteDimension,const float& playerSpriteScale,
	const sf::Vector2f& bombSpriteDimension, const float& bombSpriteScale, const float& playerBounce,
	const float& bombCountdown, const int& tileWidth, const int& tileHeight)
	: m_bombTexture(bombTexture), m_bombExplosionTexture(explosionTexture) ,m_sceneManager(sceneManager),
	m_playerSpeed(playerSpeed),
	m_playerDimension({playerSpriteDimension.x * playerSpriteScale, playerSpriteDimension.y * playerSpriteScale}),
	m_bombSpriteDimension(bombSpriteDimension), m_bombSpriteScale(bombSpriteScale), m_playerBounce(playerBounce),
	m_bombCountdown(bombCountdown), m_tileWidth(tileWidth), m_tileHeight(tileHeight)
	{
	 	m_player = std::make_unique<Player>(playerTexture,playerSpriteScale ,playerPosition, playerSpeed);
	}


void PlayerManager::HandleInput(const float& deltaTime) {
	sf::Vector2f direction;
	m_player->SetDirection(direction);
	const sf::Vector2f currentPosition = m_player->GetPosition();
	const float speed = m_player->GetSpeed();
	constexpr float width = 17 * 1.8f; // sprite size * scale
	constexpr float height = 26 * 1.8f;
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

	if(direction != sf::Vector2f{0,0}) {
		const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length;
		const sf::Vector2f newPosition = currentPosition + (direction * m_playerSpeed * deltaTime);
		
		const sf::FloatRect proposedBounds(newPosition.x, newPosition.y, m_playerDimension.x, m_playerDimension.y);
		
		if (m_sceneManager->IsCollision(proposedBounds)) {
			const sf::Vector2f adjustmentDirection = -direction * m_playerBounce; // Slight move away from the collision
			const sf::Vector2f adjustedPosition = currentPosition + adjustmentDirection;
			const sf::FloatRect adjustedBounds(adjustedPosition.x, adjustedPosition.y, m_playerDimension.x, m_playerDimension.y);
			if (!m_sceneManager->IsCollision(adjustedBounds)) {
				m_player->SetPosition(adjustedPosition);
			}
		} else {
			m_player->SetDirection(direction);
		}
		if (!IsCollidingWithBombs(newPosition, proposedBounds)) {
			m_player->SetDirection(direction);
		}
	}

	// Place bombs
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canPlaceBombs) {
		PlaceBomb();
	}
}

std::vector<Bomb*> PlayerManager::GetBombsPositions() {
	return m_bombs;
}

bool PlayerManager::IsGameOver() const {
	return m_player->GetDiedState();
}

void PlayerManager::Update(const float& deltaTime) {
	HandleInput(deltaTime);
	m_player->Update(deltaTime);
	for (auto* bomb : m_bombs) {
		if (bomb != nullptr) {
			bomb->Update(deltaTime);
			if (bomb->IsExploded()) {
				m_canPlaceBombs = true;
				const sf::Vector2f bombPosition(bomb->GetBombPosition());
				auto affectedTiles = m_sceneManager->UpdateTileState(bombPosition);
				if (IsPlayerInExplosionArea(affectedTiles)) {
					m_player->SetDiedState(true);
				}
			}
		}
	}
	m_bombs.erase(std::remove_if(m_bombs.begin(), m_bombs.end(), [](const Bomb* b){if (b != nullptr) {return b->ShouldRemoveBomb(); }}), m_bombs.end());

}

void PlayerManager::Render(sf::RenderWindow& renderWindow) const {
	m_player->Render(renderWindow);

	for (auto& bomb : m_bombs) {
		if (bomb != nullptr) {
			bomb->Render(renderWindow);
		}
	}
}

void PlayerManager::PlaceBomb() {
	// get position of player and spawn bomb
	const sf::Vector2f position = m_player->GetPosition();
	m_bombs.push_back(new Bomb(position, m_bombCountdown, 2.f, m_bombTexture, m_bombExplosionTexture));
	m_canPlaceBombs = false;
}

bool PlayerManager::IsCollidingWithBombs(const sf::Vector2f& newPosition, const sf::FloatRect& playerBounds) const {
	for (const auto& bomb: m_bombs) {
		if(bomb->GetGlobalBounds().intersects(playerBounds)) {
			return true;
		}
	}
	return false;
}

bool PlayerManager::IsPlayerInExplosionArea(const std::vector<sf::Vector2i>& affectedTiles) const {
	sf::Vector2f playerPosition = m_player->GetPosition();
	int playerTileX = static_cast<int>(playerPosition.x / m_tileWidth);
	int playerTileY = static_cast<int>(playerPosition.y / m_tileHeight);

	for (const auto& tile : affectedTiles) {
		if (tile.x == playerTileX && tile.y == playerTileY) {
			return true; // Player is in the explosion area
		}
	}

	return false; // Player is safe
}

