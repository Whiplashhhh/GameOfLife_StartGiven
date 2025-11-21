#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grille.h"
#include "Renderer.h"

int main() {
    const int width = 200;
    const int height = 150;
    const int cellSize = 10;
    const bool isToroidal = true;

    Grille game(width, height, isToroidal);
    Renderer renderer(game, cellSize);

    // Initialisation des cellules
    game.setCellAlive(1, 0, true);
    game.setCellAlive(2, 1, true);
    game.setCellAlive(0, 2, true);
    game.setCellAlive(1, 2, true);
    game.setCellAlive(2, 2, true);

    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie");
    window.setFramerateLimit(10);

    bool isPaused = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        renderer.render(window);
    }

    return 0;
}
