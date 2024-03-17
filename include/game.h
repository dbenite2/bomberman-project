#pragma once
#include <SFML/Graphics.hpp>
#include "enemyManager.h"
#include "playerManager.h"
#include "sceneManager.h"
#include "assetManager.h"

class Game {
public:
	Game(std::map<std::string, std::string>& config);
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
	void LoadTexture(const std::string& name, const std::string& route);
	void LoadGameTextures(std::map<std::string, std::string>& config);
	void InitPlayerManager(std::map<std::string, std::string>& config);
	void InitSceneManager(std::map<std::string, std::string>& config);
	void InitEnemyManager(std::map<std::string, std::string>& config);
};