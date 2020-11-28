#include "PacMan.h"

PacMan::PacMan(MapClass* map, int init_row, int init_column, int duration){
    initPlayer(map, init_row, init_column, duration);
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

        float destination_x = get_cellPositonX(m_destinationColumn, num_columns);
        float destination_z = get_cellPositonZ(m_destinationRow, num_rows);

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
    drawPlayer(red,green,blue);
}

void PacMan::drawFieldOfViewLight(){
    int x_position = m_x;
    int y_position = m_y + m_radius;
    int z_position = m_z;

    GLint position[4] = {x_position,y_position,z_position,1};
    getFieldOfViewDirection();

    GLfloat color[4]={1.0,1.0,1.0,1.0};

    glLightfv(GL_LIGHT1,GL_DIFFUSE,color);
    glLightiv(GL_LIGHT1,GL_POSITION,position);

    glLightfv (GL_LIGHT1,GL_SPOT_DIRECTION, m_lightDirection);

    glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,1.0);
    glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.0);
    glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.0);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,35);
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,25);

    glEnable(GL_LIGHT1);
}

void PacMan::getFieldOfViewDirection(){
    GLfloat direction[3];
    if(m_currentMovementDirection == TOP){
        m_lightDirection[0]=0; m_lightDirection[1]=0; m_lightDirection[2]=-1; 

    }else if(m_currentMovementDirection == BOT){
        m_lightDirection[0]=0; m_lightDirection[1]=0; m_lightDirection[2]=1; 

    }else if(m_currentMovementDirection == LEFT){
        m_lightDirection[0]=-1; m_lightDirection[1]=0; m_lightDirection[2]=0;

    }else{
        m_lightDirection[0]=1; m_lightDirection[1]=0; m_lightDirection[2]=0; 

    }
}