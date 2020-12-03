#include "../C_Map/Map.h"
#include "../C_Player/Player.h"

#ifndef __PACMAN_H
#define __PACMAN_H

class PacMan : public Player{
    int m_currentMovementDirection;
    int m_nextMovementDirection;
    GLfloat m_lightDirection[3];

public:

    PacMan(MapClass* map, int init_row, int init_column, int duration);
    
    void init_movement();
    void integrate(long t);
    void nextCell();
    bool defineNextMovement();

    void draw();
    void drawFieldOfViewLight();
    void getFieldOfViewDirection();

    void eatFood();
    bool objectiveCompleted();

    void set_movementDirection(int direction);
};

#endif