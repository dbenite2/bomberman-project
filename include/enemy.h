#pragma once
#include <SFML/Graphics.hpp>

#include "animation.h"

class Enemy {
public:
	Enemy(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& initialDirection);
	void Update(const float& deltaMS);
	void Render(sf::RenderWindow& renderWindow) const;
	void SetDirection(const sf::Vector2f& direction);
	sf::Vector2f GetPosition() const;
	void SetPosition(const sf::Vector2f& position);
	sf::Vector2f GetDirection() const;
	void SetState(bool state);
	bool IsDead() const;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_direction{0,0};
	float m_speed{80.f};
	bool m_died{false};
	Animation* m_animation{nullptr};
	sf::Vector2f m_targetPosition;
	sf::Vector2u m_windowSize{0,0};
};
