#pragma once
#include "scene.h"
#include <vector>

class SceneManager {
public:
	SceneManager(const sf::Texture& destroyableBlock, const sf::Texture& nonDestroyableBlock,
				const sf::Texture& walkableBlock, const size_t& rows, const size_t& columns,
				const int& tileWidth, const int& tileHeight);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	std::vector<sf::Vector2i> UpdateTileState(const sf::Vector2f bombPosition) const;
	bool IsCollision(const sf::FloatRect& playerBounds) const;
	std::vector<sf::Vector2f> GetValidTiles() const;
private:
	std::unique_ptr<Scene> m_scenes{ nullptr };
};