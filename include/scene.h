#pragma once
#include <SFML/Graphics.hpp>

class Scene {
public:
	Scene(const sf::Texture& destroyableBlock, const sf::Texture& nonDestroyableBlock, const sf::Texture& walkableBlock);
	~Scene();
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow);
	void GenerateMatrix() const;
	std::vector<sf::Vector2i> ChangeTileState(const sf::Vector2f bombPosition) const;
	std::vector<sf::Vector2f> GetValidTiles() const;
	bool IsCollision(const sf::FloatRect& bounds) const;
private:
	static size_t m_rows;
	static size_t m_columns;
	sf::Sprite m_destroyableBlock;
	sf::Sprite m_nonDestroyableBlock;
	sf::Sprite m_walkableBlock;
	int** m_gameMatrix;
};