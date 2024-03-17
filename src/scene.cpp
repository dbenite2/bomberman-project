#include "scene.h"

#include <iostream>
#include <random>

size_t Scene::m_rows{19};
size_t Scene::m_columns{29};

std::mt19937_64 mt(std::random_device{}());
std::uniform_int_distribution<int>dist(2,3);

constexpr int tile_width{63};
constexpr int tile_height{53}; 

Scene::Scene(const sf::Texture& destroyableBlock, const sf::Texture& nonDestroyableBlock, const sf::Texture& walkableBlock) {
	m_destroyableBlock.setTexture(destroyableBlock);
	m_nonDestroyableBlock.setTexture(nonDestroyableBlock);
	m_walkableBlock.setTexture(walkableBlock);
	m_gameMatrix = new int*[m_rows];
	GenerateMatrix();
}

Scene::~Scene() {
	if (m_gameMatrix != nullptr) {
		for (size_t i = 0; i < m_rows; i++) {
			delete[] m_gameMatrix[i];
		}
		delete[] m_gameMatrix;
		m_gameMatrix = nullptr;
	}
}

void Scene::GenerateMatrix() const {
	for (size_t i = 0; i < m_rows; i++) {
		m_gameMatrix[i] = new int[m_columns];
	}
	for (size_t i = 0; i< m_rows; i++) {
		for(size_t j = 0; j < m_columns; j++) {
			if (i == 0 || j == 0 || i == m_rows - 1 || j == m_columns - 1) {
				m_gameMatrix[i][j] = 1; // map border
				continue;
			}
			if ((i==1 &&(j==1 || j ==2)) || (j == 1 && i == 2)) {
				m_gameMatrix[i][j] = 0; // initial player position
				continue;
			}
			if (i % 2 == 0 && j % 2 == 0) {
				m_gameMatrix[i][j] = 1; // static blocks
				continue;
			}
			m_gameMatrix[i][j] = dist(mt); // 2: walkable 3: destroyable
		}
	}
}

std::vector<sf::Vector2i> Scene::ChangeTileState(const sf::Vector2f bombPosition) const {
	std::vector<sf::Vector2i> affectedTiles;
	const int bombTileX = static_cast<int>(bombPosition.x / tile_width);
	const int bombTileY = static_cast<int>(bombPosition.y / tile_height);

	const std::vector<std::pair<int, int>> offsets = {
		{1,0},
		{0,1},
		{-1,0},
		{0,-1}
	};
	affectedTiles.emplace_back(bombTileX, bombTileY);
	for (const auto& offset: offsets) {
		const int targetX = bombTileX + offset.first;
		const int targetY = bombTileY + offset.second;
		affectedTiles.emplace_back(targetX, targetY);

		// Ensure the target tile is within the bounds of the game matrix
		if (targetX >= 0 && targetX < m_columns && targetY >= 0 && targetY < m_rows) {
			if (m_gameMatrix[targetY][targetX] == 3) { // Assuming '2' represents a destroyable block
				m_gameMatrix[targetY][targetX] = 2; // Change to walkable space, assuming '0' is walkable
			}
		}
	}
	return affectedTiles;
}

std::vector<sf::Vector2f> Scene::GetValidTiles() const {
	std::vector<sf::Vector2f> validTiles;
	for(size_t i = 0; i < m_rows; i++) {
		for(size_t j = 0; j < m_columns; j++) {
			if (m_gameMatrix[i][j] == 2) {
				validTiles.emplace_back(j * tile_width, i * tile_height);
			}
 		}
	}
	return validTiles;
}


void Scene::Update(const float& deltaTime) {
	//TODO: Update scene behaviour
}

void Scene::Render(sf::RenderWindow& renderWindow) {
	float X {0};
	float Y {0};
	for(size_t i = 0; i < m_rows; i++) {
		for(size_t j = 0; j < m_columns; j++) {
			if (m_gameMatrix[i][j] == 0 || m_gameMatrix[i][j] == 2) {
				m_walkableBlock.setPosition(X,Y);
				renderWindow.draw(m_walkableBlock); // green tile
			} else if (m_gameMatrix[i][j] == 1) {
				m_nonDestroyableBlock.setPosition(X,Y);
				renderWindow.draw(m_nonDestroyableBlock); // static tile
			} else if (m_gameMatrix[i][j] == 3) {
				m_destroyableBlock.setPosition(X,Y);
				renderWindow.draw(m_destroyableBlock); // brick tile
			}
			X += tile_width;
		}
		X = 0;
		Y += tile_height;
	}
}

bool Scene::IsCollision(const sf::FloatRect& bounds) const {
	const size_t leftTile = static_cast<int> (bounds.left) / tile_width;
	const size_t rightTile = (static_cast<int>(bounds.left) + static_cast<int> (bounds.width)) / tile_width;
	const size_t topTile = static_cast<int> (bounds.top) / tile_height;
	const size_t bottomTile = (static_cast<int> (bounds.top) + static_cast<int> (bounds.height)) / tile_height;
	for(size_t y = topTile; y <= bottomTile; y++) {
		for(size_t x = leftTile; x <= rightTile; x++) {
			if (x < m_columns && y < m_rows) {
				if (m_gameMatrix[y][x] == 1 || m_gameMatrix[y][x] == 3) {
					return true; // Collision detected
				}
			}
		}
	}
	return false;
}

