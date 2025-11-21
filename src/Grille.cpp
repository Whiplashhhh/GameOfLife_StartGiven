/**
 * @file Grille.cpp
 * @brief Implementation of the Grille class for Conway's Game of Life.
 *
 * This file contains the implementation of the Grille class, which represents the grid for Conway's Game of Life.
 * The class supports both standard and toroidal (wrapping) topologies, and provides methods to update the grid,
 * set and query cell states, and count alive neighbors for each cell.
 *
 * Main functionalities:
 * - Initialize a grid of specified dimensions and topology.
 * - Update the grid to the next generation according to Game of Life rules.
 * - Set or query the state of individual cells.
 * - Count the number of alive neighbors for a given cell, considering the grid's topology.
 */
#include "Grille.h"
#include <cstdlib>

/**
 * @brief Constructor for the Grille class.
 *
 * Initializes a grid with the specified width and height, and sets whether the grid is toroidal.
 * All cells are initialized to dead (false).
 *
 * @param width The number of columns in the grid.
 * @param height The number of rows in the grid.
 * @param isToroidal If true, the grid wraps around at the edges (toroidal topology).
 */
Grille::Grille(int width, int height, bool isToroidal)
    : width(width),
      height(height),
      isToroidal(isToroidal),
      grid(width, std::vector<bool>(height, false))
{
}


/**
 * @brief Updates the grid to the next generation according to the rules of Conway's Game of Life.
 *
 * Iterates through each cell in the grid, counts its alive neighbors, and determines its next state:
 * - A live cell with 2 or 3 live neighbors survives; otherwise, it dies.
 * - A dead cell with exactly 3 live neighbors becomes alive.
 * The update is applied to a temporary grid and then copied back to the main grid.
 */
void Grille::update()
{
    nextGrid = grid;
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            int aliveNeighbors = countAliveNeighbors(x, y);
            if (grid[x][y])
            {
                nextGrid[x][y] = (aliveNeighbors == 2 || aliveNeighbors == 3);
            }
            else
            {
                nextGrid[x][y] = (aliveNeighbors == 3);
            }
        }
    }
    grid = nextGrid;
}

/**
 * @brief Returns the width of the grid.
 *
 * @return The number of columns in the grid.
 */
int Grille::getWidth() const
{
    return width;
}

/**
 * @brief Returns the height of the grid.
 *
 * @return The number of rows in the grid.
 */
int Grille::getHeight() const
{
    return height;
}

/**
 * @brief Checks if the cell at the given coordinates is alive.
 *
 * @param x The x-coordinate (column) of the cell.
 * @param y The y-coordinate (row) of the cell.
 * @return True if the cell is alive, false otherwise.
 */
bool Grille::isCellAlive(const int x, const int y) const
{
    return grid[x][y];
}

/**
 * @brief Sets the state of the cell at the given coordinates.
 *
 * @param x The x-coordinate (column) of the cell.
 * @param y The y-coordinate (row) of the cell.
 * @param alive True to set the cell as alive, false to set it as dead.
 */
void Grille::setCellAlive(int x, int y, bool alive)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        grid[x][y] = alive;
    }
}

/**
 * @brief Counts the number of alive neighbors for the cell at the given coordinates.
 *
 * Considers the grid's topology (toroidal or standard) when counting neighbors.
 *
 * @param x The x-coordinate (column) of the cell.
 * @param y The y-coordinate (row) of the cell.
 * @return The number of alive neighboring cells.
 */
int Grille::countAliveNeighbors(int x, int y) const
{
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int cdx, cdy;
            if (isToroidal)
            {
                cdx = (x + dx + width) % width;
                cdy = (y + dy + height) % height;
            }
            else
            {
                cdx = x + dx;
                cdy = y + dy;
            }
            if (dx != 0 || dy != 0)
            {
                if (cdx >= 0 && cdx < width && cdy >= 0 && cdy < height)
                {
                    count += grid[cdx][cdy];
                }
            }
        }
    }
    return count;
}

/**
 * @brief Randomly distributes alive and dead cells across the grid.
 *
 * Each cell is set to alive or dead with equal probability.
 */
void Grille::randomDistribution()
{
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            grid[x][y] = (rand() % 2 == 0) ? true : false;
        }
    }
}