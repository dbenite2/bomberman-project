#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Player.h"
#include "Bomb.h"
#include "SceneManager.h"

/**
 * Player Manager class
 * Handle the player input, how it collides and the bomb placed by it
 * also knows the state of the player.
 */
class PlayerManager {
public:
	PlayerManager(const sf::Texture& playerTexture, const sf::Texture& bombTexture,
				  const sf::Texture& explosionTexture, SceneManager* sceneManager,
				  const float& playerSpeed,const sf::Vector2f& playerPosition, const sf::Vector2f& playerSpriteDimension,
				  const float& playerSpriteScale, const sf::Vector2f& bombSpriteDimension,
				  const float& playerBounce, const float& bombCountdown, const int& tileWidth, const int& tileHeight);
	void Update(const float& deltaTime);
	void Render(sf::RenderWindow& renderWindow) const;
	void HandleInput(const float& deltaTime);
	std::vector<std::unique_ptr<Bomb>>& GetBombsPositions();
	bool IsGameOver() const;

private:
	std::unique_ptr<Player> m_player{nullptr};
	sf::Texture m_bombTexture;
	sf::Texture m_bombExplosionTexture;
	std::vector<std::unique_ptr<Bomb>> m_bombs;
	SceneManager* m_sceneManager;
	bool m_canPlaceBombs{true};
	float m_playerSpeed{0.f};
	sf::Vector2f m_playerDimension;
	sf::Vector2f m_bombSpriteDimension;
	float m_playerBounce{0.f};
	float m_bombCountdown{0.f};
	int m_tileWidth{0};
	int m_tileHeight{0};
    
	void PlaceBomb();
	bool IsCollidingWithBombs(const sf::Vector2f& newPosition) const;
	bool IsPlayerInExplosionArea(const std::vector<sf::Vector2i>& affectedTiles) const;
	static sf::Vector2f Normalize(const sf::Vector2f& source);
};

