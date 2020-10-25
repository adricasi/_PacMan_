#include "Enemies.h"
#include "../MapConstruction/MapClass.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdio.h>
#include <GL/glut.h>

void GhostEnemy::initGhostEnemy( MapClass* map, int init_row, int init_column, int duration){
    m_map = map;
    m_row = init_row;
    m_column = init_column;
    state=QUIET;
    m_movementDuration = duration;
    m_sizeBase = 1.5;

    //------------------------
    int num_columns = m_map->get_numColumns();
    int num_rows = m_map->get_numRows();
    int height = m_map->get_height();
    int width = m_map->get_width();

    float positionX = get_cellPositonX(init_column, num_columns, width);
    float positionY = get_cellPositonY(init_row, num_rows, height);
    float sizeX = get_cellSizeX(init_column, num_columns, width)/m_sizeBase;
    float sizeY = get_cellSizeY(init_row, num_rows, height)/m_sizeBase;


    set_position(init_row, init_column, positionX, positionY);
    set_size(sizeX, sizeY);   

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
        float destination_y = get_cellPositonY(m_destinationRow, num_rows, height);


        vx = (destination_x - m_x)/m_movementDuration;
        vy = (destination_y - m_y)/m_movementDuration;

        state=MOVE;
        
        time_remaining=m_movementDuration;
    }
}

void GhostEnemy::integrate(long t)
{
    
    if(state==MOVE && t<time_remaining)
    {
        m_x = m_x + vx*t;
        m_y = m_y + vy*t;
        time_remaining-=t;
    }
    else if(state==MOVE && t>=time_remaining)
    {
        m_x = m_x + vx*time_remaining;
        m_y = m_y + vy*time_remaining;
        state=QUIET;

        time_remaining=0;
        
        init_movement();
    }
}

void GhostEnemy::nextCell(){

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
    int availableCells[4];
    int availableCellsSize = 0;

    int topValue = m_map->getValue(m_row-1,m_column);
    int rightValue = m_map->getValue(m_row,m_column+1);
    int botValue = m_map->getValue(m_row+1,m_column);
    int leftValue = m_map->getValue(m_row,m_column-1);

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
        int random= m_map->randomRange(0,availableCellsSize-1);
        set_movementDirection(availableCells[random]);
    }
}

void GhostEnemy::set_movementDirection(int direction){

    m_movementDirection = direction;
}

//---------------------------------------

bool GhostEnemy::objectiveCompleted(float pacmanX, float pacmanY, float pacmanSizeX, float pacmanSizeY){
    //If the enemy position is the same as the position of pacman enemies win

    float pacmanLeftRange = pacmanX-pacmanSizeX;
    float pacmanRightRange = pacmanX+pacmanSizeX;
    float pacmanBotRange = pacmanY-pacmanSizeY;
    float pacmanTopRange = pacmanY+pacmanSizeY;

    //return (m_row == pacmanRow && m_column == pacmanColumn);
    return ((m_x>=pacmanLeftRange && m_x<=pacmanRightRange) && (m_y>=pacmanBotRange && m_y<=pacmanTopRange));
}


void GhostEnemy::draw()
{
    glColor3f(0.7,0.2,0.1);
    glBegin(GL_QUADS);
    glVertex2i(m_x-m_sizeX,m_y-m_sizeY);
    glVertex2i(m_x+m_sizeX,m_y-m_sizeY);
    glVertex2i(m_x+m_sizeX,m_y+m_sizeY);
    glVertex2i(m_x-m_sizeX,m_y+m_sizeY);
    glEnd();
}

void GhostEnemy::set_position(int row, int column, float x, float y)
{
  m_x = x;
  m_y = y;
  m_row = row;
  m_column = column;
}

void GhostEnemy::set_size(float sizeX, float sizeY){
    m_sizeX = sizeX;
    m_sizeY = sizeY;
}