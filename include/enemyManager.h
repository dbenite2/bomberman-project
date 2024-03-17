#pragma once
#include <random>
#include <vector>
#include "enemy.h"
#include "playerManager.h"
#include "sceneManager.h"
#include "../build/_deps/sfml-src/extlibs/headers/vulkan/vulkan_core.h"
#include "SFML/Graphics/Texture.hpp"

class EnemyManager {
public:
	EnemyManager(const sf::Texture& enemyTexture, SceneManager* sceneManager, PlayerManager* playerManager,const size_t difficulty, const float& enemySpeed, const sf::Vector2f& enemySpriteDimension, const float& enemySpriteScale);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	bool AllEnemiesDefeated();
private:
	std::vector<Enemy*> m_enemies{nullptr};
	sf::Texture m_enemyTexture;
	SceneManager* m_sceneManager;
	PlayerManager* m_playerManager;
	sf::Vector2f m_spriteDimensions{0.f, 0.f};
	static std::mt19937 m_rng;

	void SpawnEnemy(const float& speed, const float& scale);
	bool CheckCollisions(Enemy* enemy, const float& deltaTime);
	sf::Vector2f PickRandomDirection();
	bool IsInBombRadius(Enemy* enemy);
};
