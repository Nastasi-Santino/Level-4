#include "mouseAI.h"

void moveMouse(Mouse &mouse)
{
    mouse.pos.x += mouse.dx;
    mouse.pos.y += mouse.dy;
}

void turnMouseLeft(Mouse &mouse)
{
    if (mouse.dx == 0)
    {
        mouse.dx = -mouse.dy;
        mouse.dy = 0;
    }
    else
    {
        mouse.dy = mouse.dx;
        mouse.dx = 0;
    }
}

void turnMouseRight(Mouse &mouse)
{
    if (mouse.dx == 0)
    {
        mouse.dx = mouse.dy;
        mouse.dy = 0;
    }
    else
    {
        mouse.dy = -mouse.dx;
        mouse.dx = 0;
    }
}

void initMaze(Maze &maze)
{
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {

            MazeNode node;

            node.pos = {i, j};

            if (i <= 7)
            {
                node.distanceToCenter = j <= 7 ? (7 - i) + (7 - j) : (7 - i) + (j - 8);
            }
            else
            {
                node.distanceToCenter = j <= 7 ? (i - 8) + (7 - j) : (i - 8) + (j - 8);
            }

            node.mark = false;

            if (i - 1 >= 0)
            {
                node.neighbors.push_front({i - 1, j});
            }
            if (i + 1 < MAZE_SIZE)
            {
                node.neighbors.push_front({i + 1, j});
            }
            if (j - 1 >= 0)
            {
                node.neighbors.push_front({i, j - 1});
            }
            if (j + 1 < MAZE_SIZE)
            {
                node.neighbors.push_front({i, j + 1});
            }

            maze.nodes[i * MAZE_SIZE + j] = node;
        }
    }
}