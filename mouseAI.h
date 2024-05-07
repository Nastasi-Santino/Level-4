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

struct Mouse
{
    Position pos;
    int dx;
    int dy;
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

void moveMouse(Mouse &mouse);
void turnMouseLeft(Mouse &mouse);
void turnMouseRight(Mouse &mouse);
void initMaze(Maze &maze);

#endif