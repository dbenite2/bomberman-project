#include "bomb.h"

constexpr float holdTime = 0.2f;

Bomb::Bomb(const sf::Vector2f& position, const float& countdown,const float& explosionRadius,
    const sf::Texture& bombTexture,const sf::Texture& explosionTexture)
    : m_countdown(countdown), m_explosionRadius(explosionRadius) {
    m_bombSprite.setTexture(bombTexture);
    m_bombSprite.setPosition(position);
    m_bombSprite.setScale(sf::Vector2f(1.5f, 1.5f));
    m_explosionSprite.setTexture(explosionTexture);
    m_explosionSprite.setPosition(position);
    m_explosionSprite.setScale(sf::Vector2f(1.5f, 1.5f));
    
    m_radiusSpriteTop.setTexture(explosionTexture);
    m_radiusSpriteTop.setTextureRect(sf::IntRect(20,100,20,20));
    m_radiusSpriteTop.setPosition(position.x, position.y - 55);
    m_radiusSpriteTop.setScale(sf::Vector2f(1.8f, 3.f));
    
    m_radiusSpriteBottom.setTexture(explosionTexture);
    m_radiusSpriteBottom.setTextureRect(sf::IntRect(20,140,20,20));
    m_radiusSpriteBottom.setPosition(position.x, position.y + 28);
    m_radiusSpriteBottom.setScale(sf::Vector2f(1.8f, 3.5f));
    
    m_radiusSpriteLeft.setTexture(explosionTexture);
    m_radiusSpriteLeft.setTextureRect(sf::IntRect(20,20,20,20));
    m_radiusSpriteLeft.setPosition(position.x - 78, position.y-3);
    m_radiusSpriteLeft.setScale(sf::Vector2f(4.3f, 1.8f));
    
    m_radiusSpriteRight.setTexture(explosionTexture);
    m_radiusSpriteRight.setTextureRect(sf::IntRect(20,60,20,20));
    m_radiusSpriteRight.setPosition(position.x + 23, position.y-3);
    m_radiusSpriteRight.setScale(sf::Vector2f(5.3f, 1.8f));
    
    AddAnimation(animation_index::basic_bomb, 0,0, 22,26,3);
    AddAnimation(animation_index::bomb_explosion, 0,0, 20,20,3);
}

void Bomb::Update(float deltaTime) {
    const auto& currentAnim = m_animations[static_cast<int>(m_currentAnimation)];
    currentAnim->Update(deltaTime);
    if(!m_exploded) {
        currentAnim->ApplyToSprite(m_bombSprite);
        m_countdown -= deltaTime;
        if(m_countdown <= 0) {
            Explode(*currentAnim);
        }
    } else {
        currentAnim->ApplyToSprite(m_explosionSprite);
        m_removalDelay -= deltaTime;
        if (m_removalDelay <= 0) {
            m_remove = true;
        }
    }
}

void Bomb::Render(sf::RenderWindow& window) const {
    if (m_exploded) {
        window.draw(m_explosionSprite);
        window.draw(m_radiusSpriteTop);
        window.draw(m_radiusSpriteBottom);
        window.draw(m_radiusSpriteLeft);
        window.draw(m_radiusSpriteRight);
    } else {
        window.draw(m_bombSprite);
    }
}

bool Bomb::IsExploded() const {
    return m_exploded;
}


sf::FloatRect Bomb::GetGlobalBounds() const {
    return m_bombSprite.getGlobalBounds();
}

void Bomb::AddAnimation(animation_index index, int x, int y, int width, int height, int nFrames, bool row) {
    m_animations.emplace_back(std::make_unique<Animation>(x, y, width, height, nFrames, holdTime, row));
}

void Bomb::Explode(const Animation& currentAnimation) {
    m_currentAnimation = animation_index::bomb_explosion;
    currentAnimation.ApplyToSprite(m_explosionSprite);
    m_exploded = true;
}

sf::Vector2f Bomb::GetBombPosition() const {
    return m_bombSprite.getPosition();
}

float Bomb::GetExplosionRadius() const {
    return m_explosionRadius;
}

bool Bomb::ShouldRemoveBomb() const {
    return m_remove;
}

