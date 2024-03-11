#pragma once
#include <SFML/Graphics.hpp>

class Scene {
public:
	Scene(sf::Texture& destroyableBlock, sf::Texture& nonDestroyableBlock, sf::Texture& walkableBlock);
	// ~Scene();
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	void generateMatrix();
private:
	static size_t m_rows;
	static size_t m_columns;
	sf::Sprite m_destroyableBlock;
	sf::Sprite m_nonDestroyableBlock;
	sf::Sprite m_walkableBlock;
	int** m_gameMatrix;
};