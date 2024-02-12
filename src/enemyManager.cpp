#include "enemyManager.h"

void EnemyManager::Update(const float& deltaMS) {
	for (Enemy* enemy : m_enemies) {
		if (enemy != nullptr) {
		enemy->Update(deltaMS);
		}
	}
}