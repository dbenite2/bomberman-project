#pragma once
#include <random>
#include <vector>
#include "enemy.h"
#include "playerManager.h"
#include "sceneManager.h"
#include "SFML/Graphics/Texture.hpp"

/**
 * Enemy Manager class
 * Handle all the enemies in the game, as well its movement and if they die.
 */
class EnemyManager {
public:
	EnemyManager(const sf::Texture& enemyTexture, SceneManager* sceneManager, PlayerManager* playerManager,
				const size_t& difficulty, const float& enemySpeed, const sf::Vector2f& enemySpriteDimension,
				const float& enemySpriteScale);
	void Update(const float& deltaTime);
	void Render(sf::RenderWindow& renderWindow) const;
	bool AllEnemiesDefeated() const;
private:
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	sf::Texture m_enemyTexture;
	SceneManager* m_sceneManager{nullptr};
	PlayerManager* m_playerManager{nullptr};
	sf::Vector2f m_spriteDimensions{0.f, 0.f};
	static std::mt19937 m_rng;

	void SpawnEnemy(const float& speed, const float& scale);
	bool CheckCollisions(const Enemy* enemy, const float& deltaTime) const;
	bool IsInBombRadius(const Enemy* enemy) const;
	static sf::Vector2f PickRandomDirection();
};
