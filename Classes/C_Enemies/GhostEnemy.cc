#include "Enemies.h"

void GhostEnemy::initGhostEnemy( MapClass* map, int init_row, int init_column, int duration){
    initPlayer(map, init_row, init_column, duration);
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

        float destination_x = get_cellPositonX(m_destinationColumn, num_columns);
        float destination_z = get_cellPositonZ(m_destinationRow, num_rows);

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
    float red = 0.9;
    float green = 0.9;
    float blue = 0.8;
    drawPlayer(red,green,blue);
}