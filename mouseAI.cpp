/**
 * @brief Implementa los calculos del raton.
 **@author Nastasi Santino
 * @author Renzo Amorbello
 * @author Gregorio Matias Andrade
 *
 * @copyright Copyright (c) 2023-2024
 */
#include "mouseAI.h"
#include "API.h"

/**
 * @brief mueve el raton hacia adelante (adelante segun la orientacion del raton).
 *
 * @param mouse raton.
 */
void moveMouse(Mouse &mouse)
{
    mouse.pos.x += mouse.dx;
    mouse.pos.y += mouse.dy;
}

/**
 * @brief gira el raton hacia la izquierda (izquierda segun la orientacion del raton).
 *
 * @param mouse raton.
 */
void turnMouseLeft(Mouse &mouse)
{
    if (mouse.dx == 0)
    {
        mouse.dx = -mouse.dy;
        mouse.dy = 0;
        mouse.orientation = mouse.dx < 0 ? LEFT : RIGHT; // Cambia la orientacion segun corresponda.
    }
    else
    {
        mouse.dy = mouse.dx;
        mouse.dx = 0;
        mouse.orientation = mouse.dy < 0 ? SOUTH : NORTH;
    }
}

/**
 * @brief gira el raton hacia la derecha (derecha segun la orientacion del raton).
 *
 * @param mouse raton.
 */
void turnMouseRight(Mouse &mouse)
{
    if (mouse.dx == 0)
    {
        mouse.dx = mouse.dy;
        mouse.dy = 0;
        mouse.orientation = mouse.dx < 0 ? LEFT : RIGHT; // Cambia la orientacion segun corresponda.
    }
    else
    {
        mouse.dy = -mouse.dx;
        mouse.dx = 0;
        mouse.orientation = mouse.dy < 0 ? SOUTH : NORTH;
    }
}

/**
 * @brief inicializa las casillas del laberinto.
 *
 * @param mouse laberinto.
 */
void initMaze(Maze &maze)
{
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {

            MazeNode node;

            node.pos = {i, j};

            // Calcula la distancia al centro inicial suponiendo no paredes.

            if (i <= 7)
            {
                node.distanceToCenter = j <= 7 ? (7 - i) + (7 - j) : (7 - i) + (j - 8);
            }
            else
            {
                node.distanceToCenter = j <= 7 ? (i - 8) + (7 - j) : (i - 8) + (j - 8);
            }

            node.mark = false;

            // Guarda los vecinos.

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

            // Supone 0 paredes al comienzo.

            node.walls[0] = false;
            node.walls[1] = false;
            node.walls[2] = false;
            node.walls[3] = false;

            maze.nodes[i * MAZE_SIZE + j] = node;
        }
    }
}

/**
 * @brief dada una posicion devuelve si se puede mover hacia alli y si es el caso, la instruccion de como hacerlo.
 *
 * @param mouse raton.
 * @param pos posicion a moverse.
 * @param c caracter donde se guarda la instruccion. (f hacia adelante, l hacia la izquierda y r hacia la derecha).
 * @return devuelve si es una posicion valida o no.
 */
static bool whereTo(Mouse &mouse, Position pos, char &c)
{
    // Calcula para donde esta la posicion con respecto del raton.
    int offsetX = pos.x - mouse.pos.x;
    int offsetY = pos.y - mouse.pos.y;

    // Segun la orientacion y donde esta la casilla elige si es una casilla valida o no.
    switch (mouse.orientation)
    {
    case LEFT:

        if (offsetY == 0)
        {
            if (offsetX == -1 && !API::wallFront())
            {
                c = 'f';
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (offsetY == -1 && !API::wallLeft())
            {
                c = 'l';
                return true;
            }
            else if (offsetY == 1 && !API::wallRight())
            {
                c = 'r';
                return true;
            }
            else
            {
                return false;
            }
        }

        break;

    case RIGHT:

        if (offsetY == 0)
        {
            if (offsetX == 1 && !API::wallFront())
            {
                c = 'f';
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (offsetY == 1 && !API::wallLeft())
            {
                c = 'l';
                return true;
            }
            else if (offsetY == -1 && !API::wallRight())
            {
                c = 'r';
                return true;
            }
            else
            {
                return false;
            }
        }

        break;

    case NORTH:

        if (offsetX == 0)
        {
            if (offsetY == 1 && !API::wallFront())
            {
                c = 'f';
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (offsetX == -1 && !API::wallLeft())
            {
                c = 'l';
                return true;
            }
            else if (offsetX == 1 && !API::wallRight())
            {
                c = 'r';
                return true;
            }
            else
            {
                return false;
            }
        }

        break;

    case SOUTH:

        if (offsetX == 0)
        {
            if (offsetY == -1 && !API::wallFront())
            {
                c = 'f';
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (offsetX == 1 && !API::wallLeft())
            {
                c = 'l';
                return true;
            }
            else if (offsetX == -1 && !API::wallRight())
            {
                c = 'r';
                return true;
            }
            else
            {
                return false;
            }
        }

        break;

    default:
        return false;
    }
}

/**
 * @brief Dada una orientacion, devuelve la orientacion que girada 180 grados.
 *
 * @param orientatioToInverse orientacion a invertir.
 * @return orientacion invertida
 */
static Orientation inverseOrentiation(Orientation orientationToInverse)
{
    switch (orientationToInverse)
    {
    case RIGHT:
        return LEFT;
        break;
    case LEFT:
        return RIGHT;
        break;
    case NORTH:
        return SOUTH;
        break;
    default:
        return NORTH;
    }
}

/**
 * @brief dada una direccion, devuelve hacia donde esta en el laberinto real teniendo en cuenta la orientacion del raton.
 *
 * @param mouse raton.
 * @param orient orientacion relativa al raton.
 * @return orientacion real en el laberinto.
 */
static Orientation relativeOrientationToReal(Mouse &mouse, Orientation orient)
{
    switch (mouse.orientation)
    {

    case RIGHT:
        switch (orient)
        {
        case RIGHT:
            return SOUTH;
            break;
        case LEFT:
            return NORTH;
            break;
        case NORTH:
            return RIGHT;
            break;
        default:
            return LEFT;
        }
        break;

    case LEFT:
        switch (orient)
        {
        case RIGHT:
            return NORTH;
            break;
        case LEFT:
            return SOUTH;
            break;
        case NORTH:
            return LEFT;
            break;
        default:
            return RIGHT;
        }
        break;

    case NORTH:
        return orient;
        break;

    default:
        return inverseOrentiation(orient);
    }
}

/**
 * @brief cuando activa una pared, esa pared es compartida por 2 casillas, esta funcion activa la pared del vecino.
 *
 * @param mouse raton.
 * @param maze laberinto.
 * @param wall donde esta la pared relativo a la casilla vecina.
 */
static void setNeighborWall(Mouse &mouse, Maze &maze, Orientation wall)
{

    // La inversa de wall es donde esta la pared con respecto de la casilla del raton.
    switch (inverseOrentiation(wall))
    {
    case RIGHT:
        if (mouse.pos.x + 1 < MAZE_SIZE)
        {
            maze.nodes[(mouse.pos.x + 1) * MAZE_SIZE + mouse.pos.y].walls[wall] = true;
        }
        break;
    case LEFT:
        if (mouse.pos.x - 1 >= 0)
        {
            maze.nodes[(mouse.pos.x - 1) * MAZE_SIZE + mouse.pos.y].walls[wall] = true;
        }
        break;
    case NORTH:
        if (mouse.pos.y + 1 < MAZE_SIZE)
        {
            maze.nodes[mouse.pos.x * MAZE_SIZE + (mouse.pos.y + 1)].walls[wall] = true;
        }
        break;
    case SOUTH:
        if (mouse.pos.y - 1 >= 0)
        {
            maze.nodes[mouse.pos.x * MAZE_SIZE + (mouse.pos.y - 1)].walls[wall] = true;
        }
        break;
    }
}

/**
 * @brief revisa si hay paredes y las activa.
 *
 * @param mouse raton.
 * @param maze laberinto.
 */
void setWalls(Mouse &mouse, Maze &maze)
{
    // Pared al frente.
    if (API::wallFront())
    {
        maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y].walls[mouse.orientation] = true;
        setNeighborWall(mouse, maze, inverseOrentiation(mouse.orientation));
    }

    // Pared al frente.
    if (API::wallLeft())
    {
        maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y].walls[relativeOrientationToReal(mouse, LEFT)] = true;
        setNeighborWall(mouse, maze, inverseOrentiation(relativeOrientationToReal(mouse, LEFT)));
    }

    // Pared al frente.
    if (API::wallRight())
    {
        maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y].walls[relativeOrientationToReal(mouse, RIGHT)] = true;
        setNeighborWall(mouse, maze, inverseOrentiation(relativeOrientationToReal(mouse, RIGHT)));
    }
}

/**
 * @brief elige hacia donde va el raton, segun la distancia al centro de sus vecinos.
 *
 * @param mouse raton.
 * @param maze laberinto.
 * @return intruccion de hacia donde tiene que ir el raton. (f hacia adelante, l hacia la izquierda y r hacia la derecha).
 */
char chooseNextStep(Mouse &mouse, Maze &maze)
{

    MazeNode *actualPosNode = &maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y];

    int min = 15;
    char returnDirection = '-';

    for (auto &next : actualPosNode->neighbors)
    {

        if (!maze.nodes[next.x * MAZE_SIZE + next.y].mark)
        {
            int newMin;
            if ((newMin = maze.nodes[next.x * MAZE_SIZE + next.y].distanceToCenter) < min)
            {

                if (whereTo(mouse, next, returnDirection))
                {
                    min = newMin;
                }
            }
        }
    }

    return returnDirection;
}

/**
 * @brief revisa si una posicion es el centro del laberinto.
 *
 * @param pos posicion a analizar.
 * @return es o no una posicion del centro.
 */
static bool isPosCenter(Position pos)
{
    return (pos.x == 7 || pos.x == 8) && (pos.y == 7 || pos.y == 8);
}

/**
 * @brief revis recursivamente la distancia al centro de una casilla.
 *
 * @param mouse raton.
 * @param maze laberinto.
 * @param x posicion en x de la casilla.
 * @param y posicion en y de la casilla.
 * @param dist distancia al centro.
 * @return si llega al centro en la recursividad.
 */
bool floodFill(Mouse &mouse, Maze &maze, int x, int y, int &dist)
{
    // Check if current cell is within maze bounds and not a wall, or the center.
    if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE || maze.nodes[x * MAZE_SIZE + y].mark || isPosCenter(maze.nodes[x * MAZE_SIZE + y].pos))
    {
        if (isPosCenter(maze.nodes[x * MAZE_SIZE + y].pos))
        {
            dist = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Si llega a la altura del centro, giramos el raton para que vaya hacia el centro.

    if ((x == 7 || x == 8) && mouse.dx != 0)
    {
        if (y < 7)
        {
            while (mouse.dy != 1)
            {
                turnMouseLeft(mouse);
            }
        }
        else
        {
            while (mouse.dy != -1)
            {
                turnMouseLeft(mouse);
            }
        }
    }

    if ((y == 7 || y == 8) && mouse.dy != 0)
    {
        if (x < 7)
        {
            while (mouse.dx != 1)
            {
                turnMouseLeft(mouse);
            }
        }
        else
        {
            while (mouse.dx != -1)
            {
                turnMouseLeft(mouse);
            }
        }
    }

    // Check and move forward if no wall in front
    if (!maze.nodes[x * MAZE_SIZE + y].walls[mouse.orientation])
    {
        int newX = x + mouse.dx;
        int newY = y + mouse.dy;
        if (floodFill(mouse, maze, newX, newY, dist))
        {
            maze.nodes[newX * MAZE_SIZE + newY].distanceToCenter = dist++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (!maze.nodes[x * MAZE_SIZE + y].walls[relativeOrientationToReal(mouse, LEFT)])
    {
        // Adjust mouse orientation accordingly
        turnMouseLeft(mouse);
        // Recursively explore in the new direction
        int newX = x + mouse.dx;
        int newY = y + mouse.dy;
        if (floodFill(mouse, maze, newX, newY, dist))
        {
            maze.nodes[newX * MAZE_SIZE + newY].distanceToCenter = dist++;
            return true;
        }
        else
        {
            return false;
        }
        // Turn mouse back to original orientation after exploration
        // turnMouseRight(mouse);
    }
    else if (!maze.nodes[x * MAZE_SIZE + y].walls[relativeOrientationToReal(mouse, RIGHT)])
    {
        // Adjust mouse orientation accordingly
        turnMouseRight(mouse);
        // Recursively explore in the new direction
        int newX = x + mouse.dx;
        int newY = y + mouse.dy;
        if (floodFill(mouse, maze, newX, newY, dist))
        {
            maze.nodes[newX * MAZE_SIZE + newY].distanceToCenter = dist++;
            return true;
        }
        else
        {
            return false;
        }
        // Turn mouse back to original orientation after exploration
        // turnMouseLeft(mouse);
    }

    return false;
}