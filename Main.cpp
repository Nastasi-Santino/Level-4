#include <iostream>
#include <string>

#include "API.h"
#include "mouseAI.h"

using namespace std;

int main(void)
{

    Mouse myMouse = {{0, 0}, 0, 1, NORTH};
    Maze myMaze;
    bool noExitPath = false;

    initMaze(myMaze);

    while (true)
    {
        switch(chooseNextStep(myMouse, myMaze)){

            case 'l':
                noExitPath = false;
                API::turnLeft();
                turnMouseLeft(myMouse);
                break;

            case 'r':
                noExitPath = false;
                API::turnRight();
                turnMouseRight(myMouse);
                break;

            case 'f':
                if(noExitPath){
                    myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].mark = true;
                }
                break;

            default:
                // En este caso, el ratón encontró una pared en una celda adyacente
                myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].mark = true;
                noExitPath = true;
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
