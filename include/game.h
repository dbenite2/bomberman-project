#pragma once
#include <SFML/Graphics.hpp>
#include "enemyManager.h"
#include "playerManager.h"
#include "sceneManager.h"
#include "assetManager.h"

class Game {
public:
	Game();
	~Game();
	void Update(const float& deltaTime) const;
	void Render(sf::RenderWindow& renderWindow) const;
	bool ExitGame() const;
private:
	AssetManager m_assetManager;
	std::unique_ptr<PlayerManager> m_playerManager{nullptr};
	std::unique_ptr<EnemyManager> m_enemyManager{nullptr};
	std::unique_ptr<SceneManager> m_sceneManager{nullptr};
	bool m_gameExit{ false };
};