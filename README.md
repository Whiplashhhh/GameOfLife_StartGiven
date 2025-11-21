# Game of Life

This project is an implementation of Conway's Game of Life using C++ and SFML for rendering. The Game of Life is a cellular automaton devised by mathematician John Conway. It consists of a grid of cells that can be either alive or dead, and the state of the grid evolves over discrete time steps according to a set of rules based on the states of neighboring cells.

author: Samuel Delepoulle

## Project structure

## Building

To build the project, run the following command in the terminal:

```
cmake -S . -B build
cmake --build build
```

## Testing

To run the tests, execute the following command:

```
ctest -V --test-dir build --output-on-failure
```
