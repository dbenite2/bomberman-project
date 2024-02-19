#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    auto* game = new Game();
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Bomberman" };
    window.setFramerateLimit(60);
    sf::Clock clock;
    // while (game -> ExitGame() == false)
    // {
    //     sf::Time elapsed = clock.restart();
    //     game->Update(elapsed.asMilliseconds());
    //     game->Render(window);
    // }
    while (window.isOpen())
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