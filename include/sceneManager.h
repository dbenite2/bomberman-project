#pragma once
#include "scene.h"
#include <vector>

class SceneManager {
public:
	SceneManager(sf::Texture& destroyableBlock, sf::Texture& nonDestroyableBlock, sf::Texture& walkableBlock);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	std::vector<sf::Vector2i> UpdateTileState(const sf::Vector2f bombPosition) const;
	bool IsCollision(const sf::FloatRect& playerBounds) const;
	std::vector<sf::Vector2f> GetValidTiles() const;
private:
	std::unique_ptr<Scene> m_scenes{ nullptr };
};