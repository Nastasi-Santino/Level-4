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
    Position pivot;
    int pivotCount = 0;
    bool pivotActivated = false;
    int pivotCheck = 0;

    initMaze(myMaze);

    while (true)
    {
        setWalls(myMouse, myMaze);

        API::setColor(myMouse.pos.x, myMouse.pos.y, 'G');
        if(myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[RIGHT]){
            API::setWall(myMouse.pos.x, myMouse.pos.y, 'e');
        }
        if(myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[LEFT]){
            API::setWall(myMouse.pos.x, myMouse.pos.y, 'w');
        }
        if(myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[NORTH]){
            API::setWall(myMouse.pos.x, myMouse.pos.y, 'n');
        }
        if(myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[SOUTH]){
            API::setWall(myMouse.pos.x, myMouse.pos.y, 's');
        }

        // if(API::wallFront()){
        //     int dist = 0;
        //     Orientation mouseOrient = myMouse.orientation;
        //     turnMouseLeft(myMouse);
        //     floodFill(myMouse, myMaze, myMouse.pos.x, myMouse.pos.y, dist);
        //     while(myMouse.orientation != mouseOrient){
        //         turnMouseRight(myMouse);
        //     }
        //     turnMouseLeft(myMouse);
        //     turnMouseLeft(myMouse);
        //     floodFill(myMouse, myMaze, myMouse.pos.x, myMouse.pos.y, dist);
        //     while(myMouse.orientation != mouseOrient){
        //         turnMouseRight(myMouse);
        //     }
        //     turnMouseRight(myMouse);
        //     floodFill(myMouse, myMaze, myMouse.pos.x, myMouse.pos.y, dist);
        //     while(myMouse.orientation != mouseOrient){
        //         turnMouseRight(myMouse);
        //     }
        //     for(int i = 0; i < MAZE_SIZE; i++){
        //         for(int j = 0; j < MAZE_SIZE; j++){
        //             cerr << myMaze.nodes[i * MAZE_SIZE + j].distanceToCenter << "  ";
        //         }
        //         cerr << endl;
        //     }
        // }
        
        switch(chooseNextStep(myMouse, myMaze)){

            case 'l':
                noExitPath = false;
                API::turnLeft();
                turnMouseLeft(myMouse);
                if(!pivotActivated){
                    pivotActivated = true;
                    pivot = {myMouse.pos.x + myMouse.dx, myMouse.pos.y + myMouse.dy};
                }
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
        
        
        API::moveForward();
        moveMouse(myMouse);
        if(pivotActivated){
            pivotCheck++;
            if(myMouse.pos.x == pivot.x && myMouse.pos.y == pivot.y){
                pivotCount++;
                pivotCheck = 0;
            }
            if(pivotCount == 4){
                pivotCount = 0;
                pivotActivated = false;
                myMaze.nodes[pivot.x * MAZE_SIZE + pivot.y].mark = true;
            }
            if(pivotCheck == 10){
                pivotCount = 0;
                pivotActivated = false;

            }
        }
    }
}
