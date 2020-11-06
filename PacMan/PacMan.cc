
#include "PacMan.h"
#include "../MapConstruction/MapClass.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdio.h>
#include <GL/glut.h>

PacMan::PacMan(MapClass* map, int init_row, int init_column, int duration){
    m_map = map;
    state=QUIET;
    time_remaining = 0;
    m_movementDuration = duration;

    m_sizeDivision = 1.5;

    //------------------------
    int num_columns = m_map->get_numColumns();
    int num_rows = m_map->get_numRows();
    int height = m_map->get_height();
    int width = m_map->get_width();

    float positionX = get_cellPositonX(init_column, num_columns, width);
    float positionY = get_cellPositonY(init_row, num_rows, height);
    float positionZ = get_cellPositonZ(init_row, num_rows, height);

    float sizeX = get_cellSizeX(init_column, num_columns, width)/m_sizeDivision;
    float sizeY = get_cellSizeY(init_row, num_rows, height)/m_sizeDivision;
    float sizeZ = get_cellSizeZ(init_row, num_rows, height)/m_sizeDivision;
    float radius = get_cellSizeX(init_column, num_columns, width)/m_sizeDivision;



    set_position(init_row, init_column, positionX, positionY, positionZ);
    set_size(sizeX, sizeY, sizeZ, radius);
    eatFood();

}

//-------------Movement--------------------------------

void PacMan::init_movement(){

    if(time_remaining<=0 && defineNextMovement()){
        //init movement
        m_row = m_destinationRow;
        m_column = m_destinationColumn;
    
        int num_columns = m_map->get_numColumns();
        int num_rows = m_map->get_numRows();
        int height = m_map->get_height();
        int width = m_map->get_width();

        float destination_x = get_cellPositonX(m_destinationColumn, num_columns, width);
        float destination_z = get_cellPositonZ(m_destinationRow, num_rows, height);

        vx = (destination_x - m_x)/m_movementDuration;
        vz = (destination_z - m_z)/m_movementDuration;

        state=MOVE;
        
        time_remaining=m_movementDuration;
    }
}

void PacMan::integrate(long t)
{
    
    if(state==MOVE && t<time_remaining)
    {
        m_x = m_x + vx*t;
        m_z = m_z + vz*t;
        time_remaining-=t;
    }
    else if(state==MOVE && t>=time_remaining)
    {
        m_x = m_x + vx*time_remaining;
        m_z = m_z + vz*time_remaining;
        state=QUIET;

        time_remaining=0;
        eatFood();
        init_movement();
    }
}

bool PacMan::defineNextMovement(){
    //Define next movement, if next movement ordered is not available continue with the current movement if it is possible

    if(m_map->availableCell(get_row(),get_column(),m_nextMovementDirection)){
        m_currentMovementDirection = m_nextMovementDirection;
    }else if(!(m_map->availableCell(get_row(),get_column(),m_currentMovementDirection))){
        //Movement not available
        return false;
    }
    nextCell();
    return true;
}

void PacMan::nextCell(){
    //Obtain the next cell 

    if(m_currentMovementDirection==TOP){
        m_destinationRow = m_row-1;
        m_destinationColumn = m_column;

    }else if(m_currentMovementDirection==RIGHT){
        m_destinationRow = m_row;
        m_destinationColumn = m_column+1;

    }else if(m_currentMovementDirection==BOT){
        m_destinationRow = m_row+1;
        m_destinationColumn = m_column;

    }else if(m_currentMovementDirection==LEFT){
        m_destinationRow = m_row;
        m_destinationColumn = m_column-1;
    }
}

void PacMan::set_movementDirection(int direction){
    m_nextMovementDirection = direction;
}

//---------------------------------------------------------

void PacMan::eatFood(){
    m_map->eatFood(m_row,m_column);
}

bool PacMan::objectiveCompleted(){
    //Pacman wins when there is not more food on the map
    if(m_map->allFoodEated()){
        return true;
    }
    return false;
}

void PacMan::draw()
{
    float red = 0.1;
    float green = 0.2;
    float blue = 0.7;
    draw_sphere(m_x, m_y, m_z, m_radius, red, green, blue);
}


void PacMan::set_position(int row, int column, float x, float y, float z){
    // row and column defines the position in the map and x and y defines the position in the canvas
    m_x = x;
    m_y = y;
    m_z = z;
    m_row = row;
    m_column = column;
}

void PacMan::set_size(float sizeX, float sizeY, float sizeZ, float radius){
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_sizeZ = sizeZ;
    m_radius = radius;
}