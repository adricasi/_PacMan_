#include "Player.h"
void Player::initPlayer( MapClass* map, int init_row, int init_column, int duration){ 
    m_map = map;
    state = QUIET;
    time_remaining = 0;
    m_movementDuration = duration;
    m_sizeDivision = 1.5;

    //------------------------
    int num_columns = m_map->get_numColumns();
    int num_rows = m_map->get_numRows();
    float cellSize = m_map->get_cellSizeObtained();


    float positionX = get_cellPositonX(init_column, num_columns, cellSize);
    float positionY = get_cellPositonY(init_row, num_rows);
    float positionZ = get_cellPositonZ(init_row, num_rows, cellSize);

    float radius = get_radiusSphere(init_row, init_column, num_rows, num_columns)/m_sizeDivision;

    set_position(init_row, init_column, positionX, positionY, positionZ);
    set_radius(radius);   
}

void Player::drawPlayer(float red,float green, float blue){
    draw_sphere(m_x, m_y, m_z, m_radius, red, green, blue);
}

void Player::set_position(int row, int column, float x, float y, float z){
    // row and column defines the position in the map and x and y defines the position in the canvas
    m_x = x;
    m_y = y;
    m_z = z;
    m_row = row;
    m_column = column;
}

void Player::set_radius(float radius){
    m_radius = radius;
}