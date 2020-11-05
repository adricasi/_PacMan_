#ifndef __PACMAN_H
#define __PACMAN_H
//-----------------------------------------------
#define MOVE 1
#define QUIET 2
//-----------------------------------------------

typedef struct MapClass MapClass;
class PacMan {
    int m_movementDuration;

    int m_currentMovementDirection;
    int m_nextMovementDirection;

    MapClass* m_map;
    int m_row,m_column;   //-- Current position
    int m_destinationRow, m_destinationColumn;
    float m_x,m_y,m_z;   //-- Current position
    float vx,vz; //-- Velocity vector
    int state;

    float m_sizeDivision;
    float m_sizeX,m_sizeY,m_sizeZ;

    long time_remaining;

public:

    PacMan(MapClass* map, int init_row, int init_column, int duration);
    
    void init_movement();
    void integrate(long t);
    void nextCell();
    bool defineNextMovement();

    void draw();
    void eatFood();
    bool objectiveCompleted();

    void set_position(int row, int column, float x, float y, float z);
    void set_size(float sizeX, float sizeY, float sizeZ);
    void set_movementDirection(int direction);

    int get_row(){
        return m_row;
    }
    int get_column(){
        return m_column;
    }
    float get_y(){
        return m_y;
    }
    float get_x(){
        return m_x;
    }
    float get_sizeX(){
        return m_sizeX;
    }
    float get_sizeY(){
        return m_sizeY;
    }
};

#endif