#include "sceneManager.h"

SceneManager::SceneManager(const sf::Texture& destroyableBlock, const sf::Texture& nonDestroyableBlock,
							const sf::Texture& walkableBlock, const size_t& rows, const size_t& columns,
							const int& tileWidth, const int& tileHeight) {
	m_scenes = std::make_unique<Scene>(destroyableBlock, nonDestroyableBlock, walkableBlock, rows,
										columns, tileWidth, tileHeight);
}

void SceneManager::Update(const float& deltaMS) {
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

std::vector<sf::Vector2f> SceneManager::GetValidTiles() const {
	return m_scenes->GetValidTiles();
}

