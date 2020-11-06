#include "Enemies.h"
#include "../MapConstruction/MapClass.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdio.h>
#include <GL/glut.h>

void GhostEnemy::initGhostEnemy( MapClass* map, int init_row, int init_column, int duration){
    m_map = map;
    state = QUIET;
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

    float radius = get_cellSizeX(init_column, num_columns, width)/m_sizeDivision;

    set_position(init_row, init_column, positionX, positionY, positionZ);
    set_radius(radius);   

    init_movement();
}


//--------------Movement--------------------


void GhostEnemy::init_movement(){
    if(time_remaining<=0){
        chooseMovementDirection();
        nextCell();
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

void GhostEnemy::integrate(long t)
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
        init_movement();
    }
}

void GhostEnemy::nextCell(){
    //Obtain the next cell 

    if(m_movementDirection==TOP){
        m_destinationRow = m_row-1;
        m_destinationColumn = m_column;

    }else if(m_movementDirection==RIGHT){
        m_destinationRow = m_row;
        m_destinationColumn = m_column+1;

    }else if(m_movementDirection==BOT){
        m_destinationRow = m_row+1;
        m_destinationColumn = m_column;

    }else if(m_movementDirection==LEFT){
        m_destinationRow = m_row;
        m_destinationColumn = m_column-1;
    }
}

void GhostEnemy::chooseMovementDirection(){
    //Choose a random available direction

    int availableCells[4];
    int availableCellsSize = 0;

    int topValue = m_map->getValue(m_row-1,m_column);
    int rightValue = m_map->getValue(m_row,m_column+1);
    int botValue = m_map->getValue(m_row+1,m_column);
    int leftValue = m_map->getValue(m_row,m_column-1);

    // Available directions
    if(topValue == CORRIDOR){
        availableCells[availableCellsSize] = TOP;
        availableCellsSize = availableCellsSize+1; 
        
    }if(rightValue == CORRIDOR){
        availableCells[availableCellsSize] = RIGHT;
        availableCellsSize = availableCellsSize+1; 

    }if(botValue == CORRIDOR){
        availableCells[availableCellsSize] = BOT;
        availableCellsSize = availableCellsSize+1; 

    }if(leftValue == CORRIDOR){
        availableCells[availableCellsSize] = LEFT;
        availableCellsSize = availableCellsSize+1; 
    }

    if(availableCellsSize > 0){
        //Choose a random direction
        int random= m_map->randomRange(0,availableCellsSize-1);
        set_movementDirection(availableCells[random]);
    }
}

void GhostEnemy::set_movementDirection(int direction){
    m_movementDirection = direction;
}

//---------------------------------------

bool GhostEnemy::objectiveCompleted(float pacmanX, float pacmanZ, float pacmanRadius){
    //If an enemy touch the pacman, enemies win

    float pacmanLeftRange = pacmanX-pacmanRadius;
    float pacmanRightRange = pacmanX+pacmanRadius;
    float pacmanBotRange = pacmanZ-pacmanRadius;
    float pacmanTopRange = pacmanZ+pacmanRadius;

    return ((m_x>=pacmanLeftRange && m_x<=pacmanRightRange) && (m_z>=pacmanBotRange && m_z<=pacmanTopRange));
}


void GhostEnemy::draw()
{
    float red = 0.7;
    float green = 0.2;
    float blue = 0.1;
    draw_sphere(m_x, m_y, m_z, m_radius, red, green, blue);
}

void GhostEnemy::set_position(int row, int column, float x, float y, float z){
    // row and column defines the position in the map and x and y defines the position in the canvas
    m_x = x;
    m_y = y;
    m_z = z;
    m_row = row;
    m_column = column;
}

void GhostEnemy::set_radius(float radius){
    m_radius = radius;
}