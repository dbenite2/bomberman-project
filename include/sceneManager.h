#pragma once
#include "scene.h"
#include <vector>

class SceneManager {
public:
	SceneManager(sf::Texture& destroyableBlock, sf::Texture& nonDestroyableBlock, sf::Texture& walkableBlock);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
private:
	std::unique_ptr<Scene> m_scenes{ nullptr };
};