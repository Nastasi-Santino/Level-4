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