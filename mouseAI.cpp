#include "mouseAI.h"
#include "API.h"

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
        mouse.orientation = mouse.dx < 0 ? LEFT : RIGHT; 
    }
    else
    {
        mouse.dy = mouse.dx;
        mouse.dx = 0;
        mouse.orientation = mouse.dy < 0 ? SOUTH : NORTH; 
    }
}

void turnMouseRight(Mouse &mouse)
{
    if (mouse.dx == 0)
    {
        mouse.dx = mouse.dy;
        mouse.dy = 0;
        mouse.orientation = mouse.dx < 0 ? LEFT : RIGHT;
    }
    else
    {
        mouse.dy = -mouse.dx;
        mouse.dx = 0;
        mouse.orientation = mouse.dy < 0 ? SOUTH : NORTH; 
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

static bool whereTo(Mouse &mouse, Position pos, char &c){

    int offsetX =  pos.x - mouse.pos.x;
    int offsetY =  pos.y - mouse.pos.y;
 
    switch(mouse.orientation){
        case LEFT:

            if(offsetY == 0){
                if(offsetX == -1 && !API::wallFront()){
                    c = 'f';
                    return true;
                } else {
                    return false;
                }
            } else {
                if(offsetY == -1 && !API::wallLeft()){
                    c = 'l';
                    return true;
                } else if(offsetY == 1 && !API::wallRight()){
                    c = 'r';
                    return true;
                } else {
                    return false;
                }
            }

            break;

        case RIGHT:

            if(offsetY == 0){
                if(offsetX == 1 && !API::wallFront()){
                    c = 'f';
                    return true;
                } else {
                    return false;
                }
            } else {
                if(offsetY == 1 && !API::wallLeft()){
                    c = 'l';
                    return true;
                } else if(offsetY == -1 && !API::wallRight()){
                    c = 'r';
                    return true;
                } else {
                    return false;
                }
            }

            break;

        case NORTH:

            if(offsetX == 0){
                if(offsetY == 1 && !API::wallFront()){
                    c = 'f';
                    return true;
                } else {
                    return false;
                }
            } else {
                if(offsetX == -1 && !API::wallLeft()){
                    c = 'l';
                    return true;
                } else if(offsetX == 1 && !API::wallRight()){
                    c = 'r';
                    return true;
                } else {
                    return false;
                }
            }

            break;

        case SOUTH:

            if(offsetX == 0){
                if(offsetY == -1 && !API::wallFront()){
                    c = 'f';
                    return true;
                } else {
                    return false;
                }
            } else {
                if(offsetX == 1 && !API::wallLeft()){
                    c = 'l';
                    return true;
                } else if(offsetX == -1 && !API::wallRight()){
                    c = 'r';
                    return true;
                } else {
                    return false;
                }
            }

            break;

        default:
            return false;
    }
}

char choseNextStep(Mouse &mouse, Maze &maze){

    MazeNode * actualPosNode = &maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y];

    int min = 15; 
    char returnDirection = '-';

    for(auto &next : actualPosNode->neighbors){

        int newMin;
        if((newMin = maze.nodes[next.x * MAZE_SIZE + next.y].distanceToCenter) < min){

            if(whereTo(mouse, next, returnDirection)){
                min = newMin;
            }
        }
    }
    
    return returnDirection;

}