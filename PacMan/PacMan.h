#ifndef __PACMAN_H
#define __PACMAN_H
//-----------------------------------------------
#define MOVE 1
#define QUIET 2
//-----------------------------------------------

class PacMan {
    int m_maxRows,m_maxColumns;
    int m_height,m_width;
    int m_row,m_column;   //-- Current position
    int m_destinationRow, m_destinationColumn;
    float m_x,m_y;   //-- Current position
    float vx,vy; //-- Velocity vector
    int state;
    float m_sizeX,m_sizeY;

    long time_remaining;

public:

    PacMan(int maxRows, int maxColumns, int height, int width);
    void set_position(int row, int column, float x, float y);
    void set_size(float sizeX, float sizeY);
    void init_movement(int destination_row,int destination_column,int duration);
    void integrate(long t);
    void draw();
    int get_row(){
        return m_row;
    }
    int get_column(){
        return m_column;
    }
};

#endif
