#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "animation.h"

/**
 * Class that represents the player in the game
 */
class Player {
public:
	Player(const sf::Texture& texture, const float& spriteScale, const sf::Vector2f& position, const float& speed);
	void Update(const float& deltaTime);
	void Move(sf::Vector2f direction);
	void Render(sf::RenderWindow& renderWindow) const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetDirection() const;
	float GetSpeed() const;
	void SetPosition(const sf::Vector2f& position);
	void SetDirection(const sf::Vector2f& direction);
	void SetDiedState(bool state);
	bool GetDiedState() const;
private:
	enum class AnimationIndex {
		WalkingUp,
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		IdleUp,
		IdleDown,
		IdleLeft,
		IdleRight,
		IdleDead,
		Dead,
		Count
	};
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float m_speed{0.f};
	sf::Vector2f m_direction{0.f, 0.f};
	sf::Vector2f m_lastDirection{0.f, 0.f};
	bool m_died{false};
	std::vector<std::unique_ptr<Animation>> m_animations;
	AnimationIndex currentAnimation = AnimationIndex::IdleDown;

	void AddAnimation(AnimationIndex index, int x, int y, int width, int height, int nFrames, bool row = true);

};