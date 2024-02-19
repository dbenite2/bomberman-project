#include "assetManager.h"

bool AssetManager::LoadTexture(const std::string& name, const std::string& filename) {
    
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        // If loading failed, return false
        return false;
    }

    // Insert the texture into the map with the given name
    m_textures[name] = std::move(texture);
    return true;
}

sf::Texture& AssetManager::GetTexture(const std::string& name) {
    // Retrieve the texture by name and return a reference to it
    return m_textures.at(name);
}

void AssetManager::UnloadTexture(const std::string& name) {
    m_textures.erase(name);
}
