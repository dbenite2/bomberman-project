#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "player.h"
#include "bomb.h"
#include "sceneManager.h"

class PlayerManager {
public:
	PlayerManager(const sf::Texture& playerTexture, const sf::Texture& bombTexture, const sf::Texture& explosionTexture ,SceneManager& sceneManager);
	~PlayerManager() = default;
	void Update(const float& deltaTime);
	void Render(sf::RenderWindow& renderWindow) const;
	void HandleInput(const float& deltaTime);
private:
	std::unique_ptr<Player>m_player;
	sf::Texture m_bombTexture;
	sf::Texture m_bombExplosionTexture;
	std::vector<Bomb> m_bombs;
	SceneManager& m_sceneManager;
	bool m_canPlaceBombs{true};

	void PlaceBomb();
	bool IsCollidingWithBombs(const sf::Vector2f& newPosition, const sf::FloatRect& playerBounds) const;
	bool IsPlayerInExplosionArea(const std::vector<sf::Vector2i>& affectedTiles) const;
};
