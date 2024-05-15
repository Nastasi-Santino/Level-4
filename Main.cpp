#include <iostream>
#include <string>

#include "API.h"
#include "mouseAI.h"

using namespace std;

int main(void)
{

    Mouse myMouse = {{0, 0}, 0, 1, NORTH};
    Maze myMaze;

    initMaze(myMaze);

    while (true)
    {
        // if (!API::wallLeft())
        // {
        //     API::turnLeft();
        //     turnMouseLeft(myMouse);
        // }
        // while (API::wallFront())
        // {
        //     API::turnRight();
        //     turnMouseRight(myMouse);
        // }

        switch(chooseNextStep(myMouse, myMaze)){

            case 'l':
                API::turnLeft();
                turnMouseLeft(myMouse);
                break;

            case 'r':
                API::turnRight();
                turnMouseRight(myMouse);
                break;

            case 'f':
                break;

            default:
                // En este caso, el ratón encontró una pared en una celda adyacente
                handleWallEncounter(myMouse, myMaze);
                myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].mark = true;
                API::turnRight();
                turnMouseRight(myMouse);
                API::turnRight();
                turnMouseRight(myMouse);
        }
        
        API::setColor(myMouse.pos.x, myMouse.pos.y, 'G');
        API::moveForward();
        moveMouse(myMouse);
    }
}
