#include "enemyManager.h"

std::mt19937 EnemyManager::m_rng{std::random_device{}()};

EnemyManager::EnemyManager(const sf::Texture& enemyTexture, SceneManager* sceneManager,
							PlayerManager* playerManager,const size_t& difficulty, const float& enemySpeed,
							const sf::Vector2f& enemySpriteDimension, const float& enemySpriteScale)
							: m_enemyTexture(enemyTexture), m_sceneManager(sceneManager),
							m_playerManager(playerManager),
							m_spriteDimensions({enemySpriteDimension.x * enemySpriteScale,
								enemySpriteDimension.y * enemySpriteScale}) {
	for(size_t i = 0; i<= difficulty; i++) {
		SpawnEnemy(enemySpeed, enemySpriteScale);
	}
}

void EnemyManager::Render(sf::RenderWindow& renderWindow) const {
	for (const auto& enemy : m_enemies) {
		if (enemy != nullptr) {
			enemy->Render(renderWindow);
		}
	}
}

bool EnemyManager::AllEnemiesDefeated() const {
	return m_enemies.size() <= 1;
}

void EnemyManager::Update(const float& deltaTime) {
	for (auto& enemy : m_enemies) {
		if (enemy != nullptr) {
			if (CheckCollisions(enemy.get(), deltaTime)) {
				enemy->SetDirection(PickRandomDirection());
			}
			enemy->Update(deltaTime);
			enemy->SetState(IsInBombRadius(enemy.get()));
		}
	}
	m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(),
		[](const std::unique_ptr<Enemy>& e){ return e->IsDead(); }), m_enemies.end());
}

void EnemyManager::SpawnEnemy(const float& speed, const float& scale) {
	const std::vector<sf::Vector2f> validPositions = m_sceneManager->GetValidTiles();
    
	if (validPositions.empty()) {
		return;
	}
	
	std::uniform_int_distribution<size_t> dist(0, validPositions.size() - 1);
	
	const size_t randomIndex = dist(m_rng);
	
	const sf::Vector2f randomPosition = validPositions[randomIndex];
	m_enemies.push_back(std::make_unique<Enemy>(m_enemyTexture, randomPosition, PickRandomDirection(), speed, scale));
}

bool EnemyManager::CheckCollisions(const Enemy* enemy, const float& deltaTime) const {
	sf::Vector2f direction = enemy->GetDirection();
	const sf::Vector2f currentPosition = enemy->GetPosition();

	const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= length;
	const sf::Vector2f newPosition = currentPosition + (direction * enemy->GetSpeed() * deltaTime);
		
	const sf::FloatRect proposedBounds(newPosition.x, newPosition.y, m_spriteDimensions.x, m_spriteDimensions.y);
	return m_sceneManager->IsCollision(proposedBounds);
}

sf::Vector2f EnemyManager::PickRandomDirection()  {
	std::uniform_int_distribution<int> dist(0, 3); // 0: Up, 1: Right, 2: Down, 3: Left
	switch (dist(m_rng)) {
	case 0: return sf::Vector2f{0.f, -1.f};
	case 1: return sf::Vector2f{1.f, 0.f};
	case 2: return sf::Vector2f{0.f, 1.f};
	case 3: return sf::Vector2f{-1.f, 0.f};
	default: return sf::Vector2f{0.f, 0.f}; // Should never reach here
	}
}

bool EnemyManager::IsInBombRadius(const Enemy* enemy) const {
	float enemyPositionX = enemy->GetPosition().x;
	float enemyPositionY = enemy->GetPosition().y;
	for(auto& bomb : m_playerManager->GetBombsPositions()) {
		if (bomb && bomb->IsExploded()) {
			const sf::Vector2f& bombPos = bomb->GetBombPosition();
			int tileDistanceX = std::abs(static_cast<int>((bombPos.x - enemyPositionX) / 63));
			int tileDistanceY = std::abs(static_cast<int>((bombPos.y - enemyPositionY) / 53));

			// Check if enemy is within 1 tile distance horizontally or vertically from the bomb
			if ((tileDistanceX == 1 && tileDistanceY == 0) || (tileDistanceX == 0 && tileDistanceY == 1)) {
				return true; // Enemy is in the bomb radius
			}
		}
	}
	return false;
} 