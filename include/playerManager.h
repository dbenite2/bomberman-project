#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "player.h"
#include "bomb.h"
#include "sceneManager.h"

class PlayerManager {
public:
	PlayerManager(const sf::Texture& playerTexture, const sf::Texture& bombTexture, SceneManager& sceneManager);
	~PlayerManager() = default;
	void Update(const float& deltaTime);
	void Render(sf::RenderWindow& renderWindow) const;
	void HandleInput(const float& deltaTime);
private:
	std::unique_ptr<Player>m_player;
	sf::Texture m_bombTexture;
	std::vector<Bomb> m_bombs;
	SceneManager& m_sceneManager;

	void PlaceBomb();
	bool IsCollidingWithBombs(const sf::Vector2f& newPosition, const sf::FloatRect& playerBounds) const;
};
