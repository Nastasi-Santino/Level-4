#include <iostream>
#include <string>

#include "API.h"
#include "mouseAI.h"

int main(int argc, char* argv[]) {

    Mouse myMouse = {0, 0, 0, 1};

    API::setColor(0, 0, 'G');
    while (true) {
        if (!API::wallLeft()) {
            API::turnLeft();
            turnMouseLeft(myMouse);
        }
        while (API::wallFront()) {
            API::turnRight();
            turnMouseRight(myMouse);
        }

        API::setColor(myMouse.x, myMouse.y, 'G');
        API::moveForward();
        moveMouse(myMouse);
    }
}
