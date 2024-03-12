#include "scene.h"

#include <iostream>
#include <random>

uint64_t Scene::m_rows{19};
uint64_t Scene::m_columns{29};

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
		for(size_t j = 0; j<m_columns; j++) {
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

void Scene::ChangeTileState(const int& x, const int& y, const int& newState) const {
	m_gameMatrix[x][y] = newState;
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
				if (m_gameMatrix[y][x] == 1 || m_gameMatrix[y][x] == 3) { // Assuming '1' represents a non-walkable tile
					return true; // Collision detected
				}
			}
		}
	}
	return false;
}

