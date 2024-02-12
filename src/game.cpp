#include "game.h";

void Game::Update(const float& deltaMS) {
	m_enemyManager->Update(deltaMS);
	m_playerManager->Update(deltaMS);
	m_sceneteManager->Update(deltaMS);
}

void Game::Render(sf::RenderWindow& renderWindow) {
	// TODO: set render stuff here
	renderWindow.clear();
	// managersRenders
	renderWindow.display();
}

bool Game::ExitGame() {
	return m_gameExit;
}