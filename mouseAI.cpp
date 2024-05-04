#include "mouseAI.h"

void moveMouse(Mouse &mouse)
{
    mouse.x += mouse.dx;
    mouse.y += mouse.dy;
}

void turnMouseLeft(Mouse &mouse){
    if(mouse.dx == 0){
        mouse.dx = -mouse.dy;
        mouse.dy = 0; 
    } else {
        mouse.dy = mouse.dx;
        mouse.dx = 0; 
    }
}

void turnMouseRight(Mouse &mouse){
    if(mouse.dx == 0){
        mouse.dx = mouse.dy;
        mouse.dy = 0; 
    } else {
        mouse.dy = -mouse.dx;
        mouse.dx = 0; 
    }
}

void initMaze(Maze * maze){
    for(int i = 0; i < MAZE_SIZE; i++){
        for(int j = 0; j < MAZE_SIZE; j++){
            if(i <= 7){
                (*maze)[i][j] = j <= 7 ? (7 - i) + (7 - j) : (7 - i) + (j - 8);
            } else{
                (*maze)[i][j] = j <= 7 ? (i - 8) + (7 - j) : (i - 8) + (j - 8);
            }
        }
    }
}