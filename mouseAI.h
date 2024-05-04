#ifndef mouseAI_H
#define mouseAI_H

#define MAZE_SIZE 16

struct Mouse
{
    int x;
    int y;
    int dx;
    int dy;
};

typedef int Maze[MAZE_SIZE][MAZE_SIZE];

void moveMouse(Mouse &mouse);
void turnMouseLeft(Mouse &mouse);
void turnMouseRight(Mouse &mouse);
void initMaze(Maze * maze);


#endif 