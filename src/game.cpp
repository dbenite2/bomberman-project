#include "game.h"

Game::Game() {
	// Initialization of managers and game state
	LoadTextures("player", "../assets/player/player_sprite.png");
	LoadTextures("bomb", "../assets/player/bomb.png");
	LoadTextures("solid", "../assets/maps/solid.png");
	LoadTextures("destroyable", "../assets/maps/destroyable.png");
	LoadTextures("base", "../assets/maps/base.png");
	m_sceneManager = std::make_unique<SceneManager>(m_assetManager.GetTexture("destroyable"), m_assetManager.GetTexture("solid"), m_assetManager.GetTexture("base"));
	m_playerManager = std::make_unique<PlayerManager>(m_assetManager.GetTexture("player"), m_assetManager.GetTexture("bomb"), *m_sceneManager);
	m_enemyManager = std::make_unique<EnemyManager>();
	m_gameExit = false;
}

void Game::Update(const float& deltaTime) const {
	// m_enemyManager->Update(deltaTime);
	m_playerManager->Update(deltaTime);
	// m_sceneManager->Update(deltaTime);
}

void Game::Render(sf::RenderWindow& renderWindow) const {
	renderWindow.clear();
	m_sceneManager->Render(renderWindow);
	m_playerManager->Render(renderWindow);
	renderWindow.display();
}

bool Game::ExitGame() const {
	return m_gameExit;
}

void Game::LoadTextures(const std::string& name, const std::string& route) {
	if(!m_assetManager.LoadTexture(name, route)) {
		throw std::runtime_error("Failed to load" + name + "texture");
	}
}
