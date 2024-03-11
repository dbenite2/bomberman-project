#include "sceneManager.h"

SceneManager::SceneManager(sf::Texture& destroyableBlock, sf::Texture& nonDestroyableBlock,
	sf::Texture& walkableBlock) {
	m_scenes = std::make_unique<Scene>(destroyableBlock, nonDestroyableBlock, walkableBlock);
	m_scenes->generateMatrix();
}

void SceneManager::Update(const float& deltaMS) {
	// for (Scene* scenes : m_scenes) {
	// 	scenes->Update(deltaMS);
	// }
}

void SceneManager::Render(sf::RenderWindow& renderWindow){
	
	m_scenes->Render(renderWindow);
}
