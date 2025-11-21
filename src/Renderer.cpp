#include "Renderer.h"

Renderer::Renderer(Grille& game, int cellSize)
    : game(game), cellSize(cellSize), aliveColor(sf::Color::Green), deadColor(sf::Color::Black) {}

void Renderer::render(sf::RenderWindow& window) {
    window.clear(deadColor);
    for (int x = 0; x < game.getWidth(); ++x) {
        for (int y = 0; y < game.getHeight(); ++y) {
            if (game.isCellAlive(x, y)) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(aliveColor);
                window.draw(cell);
            }
        }
    }
    window.display();
}
