#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "player.h"

class PlayerManager {
public:
	PlayerManager(const sf::Texture& texture);
	~PlayerManager() = default;
	void Update(const float& deltaTime) const;
	void Render(sf::RenderWindow& renderWindow) const;
	void HandleInput(const float& deltaTime) const;
private:
	std::unique_ptr<Player>m_player;
};