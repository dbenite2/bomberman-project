#pragma once
#include <random>
#include <vector>
#include "enemy.h"
#include "playerManager.h"
#include "sceneManager.h"
#include "SFML/Graphics/Texture.hpp"

class EnemyManager {
public:
	EnemyManager(const sf::Texture& enemyTexture, SceneManager* sceneManager, PlayerManager* playerManager, size_t difficulty);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	bool AllEnemiesDefeated();
private:
	std::vector<Enemy*> m_enemies{nullptr};
	sf::Texture m_enemyTexture;
	SceneManager* m_sceneManager;
	PlayerManager* m_playerManager;
	static std::mt19937 m_rng;

	void SpawnEnemy();
	bool CheckCollisions(Enemy* enemy, const float& deltaTime);
	sf::Vector2f PickRandomDirection();
	bool IsInBombRadius(Enemy* enemy);
};
