#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
	Player(const sf::Texture& texture);
	void Update(const float& deltaTime);
	void Move(sf::Vector2f direction);
	void Render(sf::RenderWindow& renderWindow) const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetDirection() const;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float m_speed{30.f};
	sf::Vector2f m_lastDirection{0.f, 1.f};
};