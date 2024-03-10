#pragma once
#include <SFML/Graphics.hpp>

class Bomb {
public:
    Bomb(const sf::Vector2f position, float countdown, float explosionRadius, sf::Texture& texture);
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window) const;
    bool IsExploded() const;

private:
    sf::Sprite m_sprite;
    float m_countdown;
    float m_explosionRadius;
    bool m_exploded{false};

    void explode();
};