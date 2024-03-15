#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"

class Bomb {
public:
    Bomb(const sf::Vector2f position, float countdown, float explosionRadius,
        sf::Texture& bombTexture, sf::Texture& explosionTexture);
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
    float m_countdown;
    float m_removalDelay;
    float m_explosionRadius;
    bool m_exploded{false};
    bool m_remove{false};
    std::vector<std::unique_ptr<Animation>> m_animations;
    animation_index m_currentAnimation = animation_index::basic_bomb;
    void AddAnimation(animation_index index, int x, int y, int width, int height, int nFrames, bool row = true);
    void explode(const Animation& currentAnimation);
};