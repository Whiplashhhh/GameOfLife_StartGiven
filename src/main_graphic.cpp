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

    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie");
    window.setFramerateLimit(10);

    bool isPaused = true; // Démarrer en pause pour permettre l'édition

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Gérer les clics de souris
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x / cellSize;
                    int y = event.mouseButton.y / cellSize;

                    // Inverser l'état de la cellule
                    bool currentState = game.isCellAlive(x, y);
                    game.setCellAlive(x, y, !currentState);
                }
            }

            // Appuyer sur Espace pour démarrer/pause
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    isPaused = !isPaused;
                }
            }
        }

        // Mettre à jour seulement si non en pause
        if (!isPaused) {
            game.update();
        }

        renderer.render(window);
    }

    return 0;
}