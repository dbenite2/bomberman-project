#pragma once
#include <SFML/Graphics.hpp>

#include "animation.h"

/**
 * Class that represents an enemy in the game, it moves in random directions when it collides with a wall.
 */
class Enemy {
public:
	Enemy(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& initialDirection, const float& speed, const float& spriteScale);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow) const;
	void SetDirection(const sf::Vector2f& direction);
	sf::Vector2f GetPosition() const;
	void SetPosition(const sf::Vector2f& position);
	sf::Vector2f GetDirection() const;
	void SetState(bool state);
	bool IsDead() const;
	float GetSpeed() const;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_direction{0,0};
	float m_speed{0.f};
	bool m_died{false};
	Animation* m_animation{nullptr};
	sf::Vector2f m_targetPosition;
	sf::Vector2u m_windowSize{0,0};
};
