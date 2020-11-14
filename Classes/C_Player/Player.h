#include "../C_Map/Map.h"

#ifndef __PLAYER_H
#define __PLAYER_H

class Player{

public:

    int m_movementDuration;

    MapClass* m_map;
    int m_row,m_column;   //-- Current position
    int m_destinationRow, m_destinationColumn;
    float m_x,m_y,m_z;   //-- Current position
    float vx,vz; //-- Velocity vector
    int state;

    float m_sizeDivision;
    float m_radius;

    long time_remaining;


    void initPlayer(MapClass* map, int init_row, int init_column, int duration);

    void drawPlayer(float red,float green, float blue);

    void set_position(int row, int column, float x, float y, float z);
    void set_radius(float radius);

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
    float get_z(){
        return m_z;
    }
    float get_radius(){
        return m_radius;
    }
};

#endif