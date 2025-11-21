#ifndef GAME_H
#define GAME_H

#include <vector>

class Grille {
public:
    // Constructor
    Grille(int width, int height, bool isToroidal);
    // Methods
    // Updates the grid to the next generation
    void update();
    // Checks if a cell is alive
    [[nodiscard]] bool isCellAlive(int x, int y) const;
    // Sets the state of a cell
    void setCellAlive(int x, int y, bool alive);
    // Returns the width of the grid
    [[nodiscard]] int getWidth() const;
    // Returns the height of the grid
    [[nodiscard]] int getHeight() const;
    // Randomly distributes alive and dead cells across the grid
    void randomDistribution();

private:
    // Attributes
    int width, height;
    // Indicates if the grid is toroidal (wraps around edges)
    bool isToroidal;
    // 2D vectors representing the current and next state of the grid
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> nextGrid;
    // Helper method to count alive neighbors in a grid
    [[nodiscard]] int countAliveNeighbors(int x, int y) const;
};

#endif
