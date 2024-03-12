#include "sceneManager.h"

SceneManager::SceneManager(sf::Texture& destroyableBlock, sf::Texture& nonDestroyableBlock,
	sf::Texture& walkableBlock) {
	m_scenes = std::make_unique<Scene>(destroyableBlock, nonDestroyableBlock, walkableBlock);
}

void SceneManager::Update(const float& deltaMS) {
	// for (Scene* scenes : m_scenes) {
	// 	scenes->Update(deltaMS);
	// }
}

void SceneManager::Render(sf::RenderWindow& renderWindow){
	m_scenes->Render(renderWindow);
}

void SceneManager::UpdateTileState(const int& x, const int& y, const int& newState) const {
	m_scenes->ChangeTileState(x,y,newState);
}

bool SceneManager::IsCollision(const sf::FloatRect& playerBounds) const {
	return m_scenes->IsCollision(playerBounds);
}

