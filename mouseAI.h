/**
 * @brief Implementa los calculos del raton.
 **@author Nastasi Santino
 * @author Renzo Amorbello
 * @author Gregorio Matias Andrade
 *
 * @copyright Copyright (c) 2023-2024
 */
#ifndef mouseAI_H
#define mouseAI_H

#include <array>
#include <forward_list>

#define MAZE_SIZE 16

// Una posicion del laberiinto.
struct Position
{
    int x;
    int y;
};

// Este enum se usa para tanto para la orientacion del raton como de indice para las paredes.
enum Orientation
{
    RIGHT,
    LEFT,
    NORTH,
    SOUTH
};

// Estructura para el raton.
struct Mouse
{
    Position pos;            // Donde esta.
    int dx;                  // Como se mueve en x.
    int dy;                  // Como se mueve en y.
    Orientation orientation; // Hacia donde se orienta.
};

// Estructura para cada casilla del laberinto.
struct MazeNode
{
    Position pos;                          // Donde esta.
    int distanceToCenter;                  // Cual es su distancia hasta el centro.
    bool mark;                             // Es una casilla valida.
    std::array<bool, 4> walls;             // Paredes.
    std::forward_list<Position> neighbors; // Lista de adyacentes.
};

// Estructura para el laberinto.
struct Maze
{
    std::array<MazeNode, MAZE_SIZE * MAZE_SIZE> nodes; // Arreglo de casillas.
};

void moveMouse(Mouse &mouse);
void turnMouseLeft(Mouse &mouse);
void turnMouseRight(Mouse &mouse);
void initMaze(Maze &maze);
void setWalls(Mouse &mouse, Maze &maze);
char chooseNextStep(Mouse &mouse, Maze &maze);
bool floodFill(Mouse &mouse, Maze &maze, int x, int y, int &dist);
// void updateDistances(Maze &maze, Position pos, int distance);
// void handleWallEncounter(Mouse &mouse, Maze &maze);

#endif