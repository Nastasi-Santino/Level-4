#ifndef mouseAI_H
#define mouseAI_H

#include <array>
#include <forward_list>

#define MAZE_SIZE 16

struct Position
{
    int x;
    int y;
};

enum Orientation {RIGHT, LEFT, NORTH, SOUTH};

struct Mouse
{
    Position pos;
    int dx;
    int dy;
    Orientation orientation;
};

struct MazeNode
{
    Position pos;
    int distanceToCenter;
    bool mark;
    std::forward_list<Position> neighbors;
};

struct Maze
{
    std::array<MazeNode, MAZE_SIZE * MAZE_SIZE> nodes;
};

enum CellState {WALL, OPEN, VISITED};

void moveMouse(Mouse &mouse);
void turnMouseLeft(Mouse &mouse);
void turnMouseRight(Mouse &mouse);
void initMaze(Maze &maze);
char chooseNextStep(Mouse &mouse, Maze &maze);
void floodFill(Mouse &mouse, Maze &maze, int x, int y);

#endif