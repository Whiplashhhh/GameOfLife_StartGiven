#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Grille.h"

class Renderer {
public:
    Renderer(Grille& game, int cellSize);
    void render(sf::RenderWindow& window);

private:
    Grille& game;
    int cellSize;
    sf::Color aliveColor;
    sf::Color deadColor;
};

#endif
