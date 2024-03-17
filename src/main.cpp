#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "game.h"

std::map<std::string, std::string> ReadConfig(const std::string& filepath) {
    std::map<std::string, std::string> config;
    std::ifstream file(filepath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                config[key] = value;
            }
        }
    }

    return config;
}

int main()
{
    std::string configPath = "../config.txt"; // Adjust the path as necessary
    std::map<std::string, std::string> config = ReadConfig(configPath);
    const unsigned int width = std::stoi(config["window_width"]);
    const unsigned int height = std::stoi(config["window_height"]);
    const unsigned int frameRate = std::stoi(config["frame_rate"]);
    
    auto* game = new Game(config);
    auto window = sf::RenderWindow{ { width, height }, config["game_title"]};
    window.setFramerateLimit(frameRate);
    sf::Clock clock;
    while (game->ExitGame() == false && window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        sf::Time elapsed = clock.restart();
        game->Update(elapsed.asSeconds());
        game->Render(window);
    }
}