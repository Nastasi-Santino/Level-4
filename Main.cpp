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

        switch(choseNextStep(myMouse, myMaze)){

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

        }

        API::setColor(myMouse.pos.x, myMouse.pos.y, 'G');
        API::moveForward();
        moveMouse(myMouse);
    }
}
