#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "player.h"
#include "bomb.h"
#include "sceneManager.h"

// player speed, player position, sprite size, sprite scale, player bounce, bomb countdown, tile width and heitght 
class PlayerManager {
public:
	PlayerManager(const sf::Texture& playerTexture,const sf::Texture& bombTexture,
		const sf::Texture& explosionTexture, SceneManager* sceneManager,
		const float& playerSpeed,const sf::Vector2f& playerPosition, const sf::Vector2f& playerSpriteDimension,
		const float& playerSpriteScale,const sf::Vector2f& bombSpriteDimension,const float& bombSpriteScale,
		const float& playerBounce, const float& bombCountdown, const int& tileWidth, const int& tileHeight);
	~PlayerManager() = default;
	void Update(const float& deltaTime);
	void Render(sf::RenderWindow& renderWindow) const;
	void HandleInput(const float& deltaTime);
	std::vector<Bomb*> GetBombsPositions();
	bool IsGameOver() const;
private:
	std::unique_ptr<Player>m_player{nullptr};
	sf::Texture m_bombTexture;
	sf::Texture m_bombExplosionTexture;
	std::vector<Bomb*> m_bombs{nullptr};
	SceneManager* m_sceneManager;
	bool m_canPlaceBombs{true};
	const float m_playerSpeed{0.0f};
	const sf::Vector2f m_playerDimension{0.f, 0.f};
	const sf::Vector2f m_bombSpriteDimension{0.f, 0.f};
	const float m_bombSpriteScale{0.0f};
	const float m_playerBounce{0.0f};
	const float m_bombCountdown{0.0f};
	const int m_tileWidth{0};
	const int m_tileHeight{0};
	
	void PlaceBomb();
	bool IsCollidingWithBombs(const sf::Vector2f& newPosition, const sf::FloatRect& playerBounds) const;
	bool IsPlayerInExplosionArea(const std::vector<sf::Vector2i>& affectedTiles) const;
};
