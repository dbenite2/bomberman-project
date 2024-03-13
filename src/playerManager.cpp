#include "playerManager.h"
 
PlayerManager::PlayerManager(const sf::Texture& playerTexture, const sf::Texture& bombTexture, SceneManager& sceneManager)
	: m_bombTexture(bombTexture), m_sceneManager(sceneManager) {
	m_player = std::make_unique<Player>(playerTexture);
}

void PlayerManager::HandleInput(const float& deltaTime) {
	sf::Vector2f direction;
	const sf::Vector2f currentPosition = m_player->GetPosition();
	const float speed = m_player->GetSpeed();
	constexpr float width = 17 * 1.5f; // sprite size * scale
	constexpr float height = 26 * 1.5f;
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
		const sf::Vector2f newPosition = currentPosition + (direction * speed * deltaTime);
		
		const sf::FloatRect proposedBounds(newPosition.x, newPosition.y, width, height);
		
		if (m_sceneManager.IsCollision(proposedBounds)) {
			const sf::Vector2f adjustmentDirection = -direction * 5.f; // Slight move away from the collision
			const sf::Vector2f adjustedPosition = currentPosition + adjustmentDirection;
			const sf::FloatRect adjustedBounds(adjustedPosition.x, adjustedPosition.y, width, height);
			if (!m_sceneManager.IsCollision(adjustedBounds)) {
				m_player->SetPosition(adjustedPosition);
			}
		} else {
			m_player->Move(direction * deltaTime);
		}
		if (!IsCollidingWithBombs(newPosition, proposedBounds)) {
			m_player->Move(direction * deltaTime);
		}
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
		if (bomb.IsExploded()) {
			const sf::Vector2f bombPosition(bomb.GetBombPosition());
			auto affectedTiles = m_sceneManager.UpdateTileState(bombPosition);
			if (IsPlayerInExplosionArea(affectedTiles)) {
				m_player->SetDiedState(true);
			}
		}
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
	const sf::Vector2f position = m_player->GetPosition();
	m_bombs.emplace_back(position, 3.0f, 2.f, m_bombTexture);
}

bool PlayerManager::IsCollidingWithBombs(const sf::Vector2f& newPosition, const sf::FloatRect& playerBounds) const {
	for (const auto& bomb: m_bombs) {
		if(bomb.GetGlobalBounds().intersects(playerBounds)) {
			return true;
		}
	}
	return false;
}

bool PlayerManager::IsPlayerInExplosionArea(const std::vector<sf::Vector2i>& affectedTiles) const {
	sf::Vector2f playerPosition = m_player->GetPosition();
	int playerTileX = static_cast<int>(playerPosition.x / 63);
	int playerTileY = static_cast<int>(playerPosition.y / 53);

	for (const auto& tile : affectedTiles) {
		if (tile.x == playerTileX && tile.y == playerTileY) {
			return true; // Player is in the explosion area
		}
	}

	return false; // Player is safe
}

