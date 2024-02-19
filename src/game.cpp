#include "game.h"

Game::Game() {
	// Initialization of managers and game state
	if(!m_assetManager.LoadTexture("player", "../assets/player/player.png")) {
		throw std::runtime_error("Failed to load player texture");
	}
	m_playerManager = std::make_unique<PlayerManager>(m_assetManager.GetTexture("player"));
	m_enemyManager = std::make_unique<EnemyManager>();
	m_sceneManager = std::make_unique<SceneManager>();
	m_gameExit = false;
}

void Game::Update(const float& deltaTime) const {
	// m_enemyManager->Update(deltaTime);
	m_playerManager->Update(deltaTime);
	// m_sceneManager->Update(deltaTime);
}

void Game::Render(sf::RenderWindow& renderWindow) const {
	renderWindow.clear();
	m_playerManager->Render(renderWindow);
	renderWindow.display();
}

bool Game::ExitGame() const {
	return m_gameExit;
}