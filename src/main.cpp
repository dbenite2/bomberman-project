#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    Game* game = new Game();
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);
    sf::Clock clock;
    while (game -> ExitGame() == false)
    {
        sf::Time elapsed = clock.restart();
        game->Update(elapsed.asMilliseconds());
        game->Render(window);
    }
}