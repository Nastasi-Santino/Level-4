/**
 * @brief Mighty Mouse.
 **@author Nastasi Santino
 * @author Renzo Amorbello
 * @author Gregorio Matias Andrade
 *
 * @copyright Copyright (c) 2023-2024
 */
#include <iostream>
#include <string>

#include "API.h"
#include "mouseAI.h"

using namespace std;

int main(void)
{
    // Creamos un raton y un laberinto
    Mouse myMouse = {{0, 0}, 0, 1, NORTH};
    Maze myMaze;

    // algunas variables para casos limites.
    bool noExitPath = false;
    Position pivot;
    int pivotCount = 0;
    bool pivotActivated = false;
    int pivotCheck = 0;

    // inicializamos el laberinto
    initMaze(myMaze);

    while (true)
    {

        // Guardamos las paredes en el laberinto, y las pintamos en el laberinto.
        setWalls(myMouse, myMaze);

        API::setColor(myMouse.pos.x, myMouse.pos.y, 'G');
        if (myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[RIGHT])
        {
            API::setWall(myMouse.pos.x, myMouse.pos.y, 'e');
        }
        if (myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[LEFT])
        {
            API::setWall(myMouse.pos.x, myMouse.pos.y, 'w');
        }
        if (myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[NORTH])
        {
            API::setWall(myMouse.pos.x, myMouse.pos.y, 'n');
        }
        if (myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].walls[SOUTH])
        {
            API::setWall(myMouse.pos.x, myMouse.pos.y, 's');
        }

        // Buscamos el siguiente paso.
        switch (chooseNextStep(myMouse, myMaze))
        {

        // Caso girar a izquierda.
        case 'l':
            noExitPath = false;
            API::turnLeft();
            turnMouseLeft(myMouse);
            if (!pivotActivated) // si el pivote no esta activado
            {
                pivotActivated = true;                                            // lo activo
                pivot = {myMouse.pos.x + myMouse.dx, myMouse.pos.y + myMouse.dy}; // y pongo la posicion siguiente como pivote.
            }
            break;

        // Caso girar a derecha.
        case 'r':
            noExitPath = false;
            API::turnRight();
            turnMouseRight(myMouse);
            break;

        // Caso seguir hacia adelante.
        case 'f':
            if (noExitPath) // si estamos saliendo de un callejon si salida, marcamos las casillas
            {
                myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].mark = true;
            }
            break;

        default:
            // En este caso, el ratón encontró una pared en todas las celdas adyacentes
            myMaze.nodes[myMouse.pos.x * MAZE_SIZE + myMouse.pos.y].mark = true; // Marcamos la casilla para no volver.
            noExitPath = true;                                                   // Activamos el flag para indicar que estamos en un callejon sin salida. Se desactiva cuando giras.
            API::turnRight();
            turnMouseRight(myMouse);
            API::turnRight();
            turnMouseRight(myMouse);
        }

        // Movemos el raton.
        API::moveForward();
        moveMouse(myMouse);

        // Si el pivote esta activado
        if (pivotActivated)
        {
            pivotCheck++;                                             // cuento cuantas veces revise el pivote.
            if (myMouse.pos.x == pivot.x && myMouse.pos.y == pivot.y) // si el raton esta sobre el pivote aumento el contador.
            {
                pivotCount++;
                pivotCheck = 0; // reinicio el contador de revisar.
            }
            if (pivotCount == 4) // si llega 4 veces al mismo lugar, esta en un loop.
            {
                pivotCount = 0;
                pivotActivated = false;
                myMaze.nodes[pivot.x * MAZE_SIZE + pivot.y].mark = true; // marco la posicion.
            }
            if (pivotCheck == 10)
            {
                pivotCount = 0;
                pivotActivated = false;
            }
        }
    }
}
