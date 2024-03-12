#pragma once
#include "scene.h"
#include <vector>

class SceneManager {
public:
	SceneManager(sf::Texture& destroyableBlock, sf::Texture& nonDestroyableBlock, sf::Texture& walkableBlock);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	bool IsValidTile(const int& x, const int& y)const;
	void UpdateTileState(const int& x, const int& y, const int& newState) const;
	bool IsCollision(const sf::FloatRect& playerBounds) const;
private:
	std::unique_ptr<Scene> m_scenes{ nullptr };
};