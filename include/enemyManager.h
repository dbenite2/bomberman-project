#pragma once
#include <vector>
#include "enemy.h"

class EnemyManager {
public:
	void Update(const float& deltaMS);
	void Render();
private:
	std::vector<Enemy*> m_enemies{nullptr};
};