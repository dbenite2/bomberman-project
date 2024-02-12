#pragma once
#include "enemyManager.h";
#include "playerManager.h";
#include "sceneManager.h";
#include <SFML/Graphics.hpp>

class Game {
public:
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	bool ExitGame();
private:
	EnemyManager* m_enemyManager{ nullptr };
	PlayerManager* m_playerManager{ nullptr };
	SceneManager* m_sceneteManager{ nullptr };
	bool m_gameExit{ false };
};