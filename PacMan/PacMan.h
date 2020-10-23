#ifndef __PACMAN_H
#define __PACMAN_H
//-----------------------------------------------
#define MOVE 1
#define QUIET 2
//-----------------------------------------------

typedef struct MapClass MapClass;
class PacMan {
    int m_maxRows,m_maxColumns;
    int m_height,m_width;

    int m_movementDuration;
    int m_movementDirection;
    //int m_movementNextDirection;

    MapClass* m_map;
    int m_row,m_column;   //-- Current position
    int m_destinationRow, m_destinationColumn;
    float m_x,m_y;   //-- Current position
    float vx,vy; //-- Velocity vector
    int state;
    float m_sizeX,m_sizeY;

    long time_remaining;

public:

    PacMan(MapClass* map, int init_row, int init_column, int duration);
    void set_position(int row, int column, float x, float y);
    void set_size(float sizeX, float sizeY);
    void init_movement();
    void integrate(long t);
    void nextCell();
    void draw();
    void eatFood();
    bool objectiveCompleted();

    int get_row(){
        return m_row;
    }
    int get_column(){
        return m_column;
    }

    void set_movementDirection(int direction);
};

#endif
