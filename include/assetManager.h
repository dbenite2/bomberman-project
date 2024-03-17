#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

/**
 * class to handle resources in the game
 */
class AssetManager {
public:
    // Loads a texture and stores it with the specified name
    bool LoadTexture(const std::string& name, const std::string& filename);

    // Retrieves a reference to a texture by name
    sf::Texture& GetTexture(const std::string& name);

    // Removes a texture from the manager
    void UnloadTexture(const std::string& name);
private:
    std::unordered_map<std::string, sf::Texture> m_textures; // Stores textures by name
};
