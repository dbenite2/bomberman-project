#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Animation {
public:
    Animation() = default;
    Animation(const int& x, const int& y, const int& width, const int& height,const int& nFrames,
        const float& holdTime, bool row = true) :  m_holdTime(holdTime), m_animate(nFrames > 1) {
        for (int i = 0;i < nFrames; ++i) {
            sf::IntRect frame(x + (row ? i * width : 0), y + (row ? 0 : i * height), width, height);
            m_frames.push_back(frame);
        }
    }
    void ApplyToSprite(sf::Sprite& s) const {
        if(!m_frames.empty()) {
            s.setTextureRect(m_frames[m_iFrame]);
        }
    }
    void Update(float dt) {
        if(!m_animate) return;
        m_time += dt;
        while (m_time >= m_holdTime && m_animate) {
            m_time -= m_holdTime;
            Advance();
        }
    }
private:
    void Advance() {
        ++m_iFrame %= m_frames.size();
    }
	
    std::vector<sf::IntRect> m_frames;
    float m_holdTime{0.0f};
    int m_iFrame{0};
    float m_time{0.0f};
    bool m_animate{false};
};