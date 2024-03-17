#pragma once
#include <SFML/Graphics.hpp>

/**
 * Class that draws and keeps the current world state
 */

class Scene {
public:
	Scene(const sf::Texture& destroyableBlock, const sf::Texture& nonDestroyableBlock,
		const sf::Texture& walkableBlock, const size_t& rows, const size_t& columns,
		const int& tileWidth, const int& tileHeight);
	~Scene();
	void Render(sf::RenderWindow& renderWindow);
	void GenerateMatrix() const;
	std::vector<sf::Vector2i> ChangeTileState(const sf::Vector2f bombPosition) const;
	std::vector<sf::Vector2f> GetValidTiles() const;
	bool IsCollision(const sf::FloatRect& bounds) const;
private:
	enum m_blockIndex {
		initial,
		solid,
		grass,
		brick,
	};
	size_t m_rows{0};
	size_t m_columns{0};
	int m_tileWidth{0};
	int m_tileHeight{0};
	sf::Sprite m_destroyableBlock;
	sf::Sprite m_nonDestroyableBlock;
	sf::Sprite m_walkableBlock;
	int** m_gameMatrix;
};