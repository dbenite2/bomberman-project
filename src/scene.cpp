#include "scene.h"
#include <random>

size_t Scene::m_rows{13};
size_t Scene::m_columns{20};

std::mt19937_64 mt(std::random_device{}());
std::uniform_int_distribution<int>dist(2,3);

Scene::Scene(sf::Texture& destroyableBlock, sf::Texture& nonDestroyableBlock, sf::Texture& walkableBlock) {
	m_destroyableBlock.setTexture(destroyableBlock);
	m_destroyableBlock.setScale(1.5f, 1.5f);
	m_nonDestroyableBlock.setTexture(nonDestroyableBlock);
	m_nonDestroyableBlock.setScale(1.5f, 1.5f);
	m_walkableBlock.setTexture(walkableBlock);
	m_walkableBlock.setScale(1.5f, 1.5f);
	m_gameMatrix = new int*[m_rows];
	generateMatrix();
}

void Scene::generateMatrix() {
	for (size_t i = 0; i < m_rows; i++) {
		m_gameMatrix[i] = new int[m_columns];
	}
	for (size_t i = 0; i< m_rows; i++) {
		for(size_t j = 0; j<m_columns; j++) {
			if (i == 0 || j == 0 || i == m_rows - 1 || j == m_columns - 1) {
				m_gameMatrix[i][j] = 1;
				continue;
			}
			if ((i==1 &&(j==1 || j ==2)) || (j == 1 && i == 2)) {
				m_gameMatrix[i][j] = 0;
				continue;
			}
			if (i % 2 == 0 && j % 2 == 0) {
				m_gameMatrix[i][j] = 1;
				continue;
			}
			m_gameMatrix[i][j] = dist(mt);
		}
	}
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
				renderWindow.draw(m_walkableBlock);
			} else if (m_gameMatrix[i][j] == 1) {
				m_nonDestroyableBlock.setPosition(X,Y);
				renderWindow.draw(m_nonDestroyableBlock);
			} else if (m_gameMatrix[i][j] == 3) {
				m_destroyableBlock.setPosition(X,Y);
				renderWindow.draw(m_destroyableBlock);
			}
			X += 93;
		}
		X = 0;
		Y += 80;
	}
}
