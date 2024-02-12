#pragma once
#include "enemy.h";
#include <vector>

class EnemyManager {
public:
	void Update(const float& deltaMS);
	void Render();
private:
	std::vector<Enemy*> m_enemies{nullptr};
};