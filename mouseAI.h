#ifndef mouseAI_H
#define mouseAI_H

struct Mouse
{
    int x;
    int y;
    int dx;
    int dy;
};

void moveMouse(Mouse &mouse);
void turnMouseLeft(Mouse &mouse);
void turnMouseRight(Mouse &mouse);


#endif 