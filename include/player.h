#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, bool row, bool animated) : animate(animated) {
		if (animate) {
			if (row) {
				for (int i = 0; i< nFrames; i++ ) {
					frames[i] = {x + i * width, y,  width, height};
				}
			} else {
				for (int i = 0; i< nFrames; i++ ) {
					frames[i] = {x, y + i * height,  width, height};
				}
			}
		} else {
			frames[0] = {x, y, width, height};
		}
	}
	void ApplyToSprite(sf::Sprite& s) const {
		s.setTextureRect(frames[iFrame]);
	}
	void Update(float dt) {
		time += dt;
		while (time >= holdTime) {
			time -= holdTime;
			if (animate) Advance();
		}
	}
private:
	void Advance() {
		if (++iFrame  >= nFrames) {
			iFrame = 0;
		}
	}
	inline static constexpr int nFrames = 3;
	float holdTime = 0.08f;
	sf::Texture texture;
	sf::IntRect frames[nFrames];
	int iFrame = 0;
	float time = 0.0f;
	bool animate{false};
};

class Player {
public:
	Player(const sf::Texture& texture);
	void Update(const float& deltaTime);
	void Move(sf::Vector2f direction);
	void Render(sf::RenderWindow& renderWindow) const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetDirection() const;
	float GetSpeed() const;
	sf::Vector2f GetSize() const;
	sf::FloatRect GetGlobalBounds();
	void SetPosition(const sf::Vector2f& position);
	void SetDirection(const sf::Vector2f& direction);
	void SetDiedState(bool state);
private:
	enum class AnimationIndex {
		WalkingUp,
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		IdleUp,
		IdleDown,
		IdleLeft,
		IdleRigth,
		IdleDead,
		Dead,
		Count
	};
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	// sf::Vector2f m_size{36.f, 50.f};
	sf::Vector2f m_size{0.03f, 0.03f};
	float m_speed{80.f};
	sf::Vector2f m_direction{0.f, 0.f};
	sf::Vector2f m_lastDirection{0.f, 0.f};
	bool m_died{false};
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::IdleDown;
};