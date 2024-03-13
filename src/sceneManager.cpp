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

std::vector<sf::Vector2i> SceneManager::UpdateTileState(const sf::Vector2f bombPosition) const {
	return m_scenes->ChangeTileState(bombPosition);
}

bool SceneManager::IsCollision(const sf::FloatRect& playerBounds) const {
	return m_scenes->IsCollision(playerBounds);
}

