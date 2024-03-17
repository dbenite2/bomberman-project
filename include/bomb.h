#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"

/**
 * Class that represents a bomb in the game
 * @param position: the position where the bomb is going to be placed
 * @param countdown: the amount of time the bomb will be visible
 * @param explosionRadius: the length of the explosion
 * @param bombTexture: The texture of the bomb sprite
 * @param explosionTexture: The texture of the explosion sprites
 * */

class Bomb {
public:
    Bomb(const sf::Vector2f& position, const float& countdown, const float& explosionRadius,
       const sf::Texture& bombTexture, const sf::Texture& explosionTexture);
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window) const;
    bool IsExploded() const;
    sf::FloatRect GetGlobalBounds() const;
    sf::Vector2f GetBombPosition() const;
    float GetExplosionRadius() const;
    bool ShouldRemoveBomb() const;
private:
    enum class animation_index {
        basic_bomb,
        bomb_explosion,
        explosion_radius,
        count
    };
    sf::Sprite m_bombSprite;
    sf::Sprite m_explosionSprite;
    sf::Sprite m_radiusSpriteTop;
    sf::Sprite m_radiusSpriteBottom;
    sf::Sprite m_radiusSpriteLeft;
    sf::Sprite m_radiusSpriteRight;
    float m_countdown{0.f};
    float m_removalDelay{0.5f};
    float m_explosionRadius{0.f};
    bool m_exploded{false};
    bool m_remove{false};
    std::vector<std::unique_ptr<Animation>> m_animations;
    animation_index m_currentAnimation = animation_index::basic_bomb;
    void AddAnimation(animation_index index, int x, int y, int width, int height, int nFrames, bool row = true);
    void Explode(const Animation& currentAnimation);
};