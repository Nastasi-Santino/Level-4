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

            node.walls[0] = false;
            node.walls[1] = false;
            node.walls[2] = false;
            node.walls[3] = false;

            maze.nodes[i * MAZE_SIZE + j] = node;
        }
    }
}

static bool whereTo(Mouse &mouse, Position pos, char &c)
{

    int offsetX = pos.x - mouse.pos.x;
    int offsetY = pos.y - mouse.pos.y;

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

static void setNeighnourWall(Mouse &mouse, Maze &maze, Orientation wall)
{

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

void setWalls(Mouse &mouse, Maze &maze)
{

    if (API::wallFront())
    {
        maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y].walls[mouse.orientation] = true;
        setNeighnourWall(mouse, maze, inverseOrentiation(mouse.orientation));
    }

    if (API::wallLeft())
    {
        maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y].walls[relativeOrientationToReal(mouse, LEFT)] = true;
        setNeighnourWall(mouse, maze, inverseOrentiation(relativeOrientationToReal(mouse, LEFT)));
    }

    if (API::wallRight())
    {
        maze.nodes[mouse.pos.x * MAZE_SIZE + mouse.pos.y].walls[relativeOrientationToReal(mouse, RIGHT)] = true;
        setNeighnourWall(mouse, maze, inverseOrentiation(relativeOrientationToReal(mouse, RIGHT)));
    }
}

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

static bool isPosCenter(Position pos)
{
    return (pos.x == 7 || pos.x == 8) && (pos.y == 7 || pos.y == 8);
}

void floodFill(Mouse &mouse, Maze &maze, int x, int y)
{
    // Check if current cell is within maze bounds and not a wall or already visited
    if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE || maze.nodes[x * MAZE_SIZE + y].mark || isPosCenter(maze.nodes[x * MAZE_SIZE + y].pos))
    {
        return;
    }

    // Mark current cell as visited
    maze.nodes[x * MAZE_SIZE + y].mark = true;

    // Recursively explore neighboring cells

    // Check and move forward if no wall in front
    if (!API::wallFront())
    {
        int newX = x + mouse.dx;
        int newY = y + mouse.dy;
        floodFill(mouse, maze, newX, newY);
    }

    // Check and turn left if no wall on the left
    if (!API::wallLeft())
    {
        // Adjust mouse orientation accordingly
        turnMouseLeft(mouse);
        // Recursively explore in the new direction
        floodFill(mouse, maze, x, y);
        // Turn mouse back to original orientation after exploration
        turnMouseRight(mouse);
    }

    // Check and turn right if no wall on the right
    if (!API::wallRight())
    {
        // Adjust mouse orientation accordingly
        turnMouseRight(mouse);
        // Recursively explore in the new direction
        floodFill(mouse, maze, x, y);
        // Turn mouse back to original orientation after exploration
        turnMouseLeft(mouse);
    }
}

void updateDistances(Maze &maze, Position pos, int distance)
{
    // Verificar si la posición está dentro del laberinto y si la celda aún no ha sido visitada
    if (pos.x < 0 || pos.x >= MAZE_SIZE || pos.y < 0 || pos.y >= MAZE_SIZE || maze.nodes[pos.x * MAZE_SIZE + pos.y].distanceToCenter != -1)
    {
        return;
    }

    // Actualizar la distancia al centro de la celda
    maze.nodes[pos.x * MAZE_SIZE + pos.y].distanceToCenter = distance;

    // Propagar la actualización recursivamente a las celdas adyacentes
    updateDistances(maze, {pos.x - 1, pos.y}, distance + 1); // Izquierda
    updateDistances(maze, {pos.x + 1, pos.y}, distance + 1); // Derecha
    updateDistances(maze, {pos.x, pos.y - 1}, distance + 1); // Arriba
    updateDistances(maze, {pos.x, pos.y + 1}, distance + 1); // Abajo
}

// Función para manejar cuando el ratón encuentra una pared en una celda adyacente
void handleWallEncounter(Mouse &mouse, Maze &maze)
{
    // Actualizar las distancias al centro de las celdas adyacentes
    updateDistances(maze, {mouse.pos.x - 1, mouse.pos.y}, 1); // Izquierda
    updateDistances(maze, {mouse.pos.x + 1, mouse.pos.y}, 1); // Derecha
    updateDistances(maze, {mouse.pos.x, mouse.pos.y - 1}, 1); // Arriba
    updateDistances(maze, {mouse.pos.x, mouse.pos.y + 1}, 1); // Abajo
}
