
#include "PacMan.h"
#include "../MapConstruction/MapClass.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdio.h>
#include <GL/glut.h>

PacMan::PacMan(MapClass* map, int init_row, int init_column)
{
    m_map = map;
    m_row = init_row;
    m_column = init_column;
    state=QUIET;

    //------------------------
    printf("PACMAN INI \n");
    int num_columns = m_map->get_numColumns();
    int num_rows = m_map->get_numRows();
    int height = m_map->get_height();
    int width = m_map->get_width();

    float positionX = get_cellPositonX(init_column, num_columns, width);
    float positionY = get_cellPositonY(init_row, num_rows, height);
    float sizeX = get_cellSizeX(init_column, num_columns, width)/1.5;
    float sizeY = get_cellSizeY(init_row, num_rows, height)/1.5;

    printf("x:%f, y:%f, sx: %f sy:%f\n", positionX,positionY,sizeX,sizeY);

    set_position(init_row, init_column, positionX, positionY);
    set_size(sizeX, sizeY);
    eatFood();

}

void PacMan::set_position(int row, int column, float x, float y)
{
  m_x = x;
  m_y = y;
  m_row = row;
  m_column = column;
}

void PacMan::set_size(float sizeX, float sizeY){
    m_sizeX = sizeX;
    m_sizeY = sizeY;
}

void PacMan::init_movement(int destination_row,int destination_column,int duration)
{
    if(time_remaining<=0){
        m_destinationRow = destination_row;
        m_destinationColumn = destination_column;

        int num_columns = m_map->get_numColumns();
        int num_rows = m_map->get_numRows();
        int height = m_map->get_height();
        int width = m_map->get_width();


        float destination_x = get_cellPositonX(destination_column, num_columns, width);
        float destination_y = get_cellPositonY(destination_row, num_rows, height);

        //printf("dr:%d, dc:%d, dx: %f, dy: %f| x:%f y:%f\n",destination_row, destination_column, destination_x,destination_y,m_x,m_y);

        vx = (destination_x - m_x)/duration;
        vy = (destination_y - m_y)/duration;
        //printf("vx:%f vy:%f\n",vx,vy);

        state=MOVE;
        
        time_remaining=duration;
    }
}

void PacMan::integrate(long t)
{
    
    if(state==MOVE && t<time_remaining)
    {
        //printf("t:%ld\n",t);
        //printf("newx:%f,newy:%f tr:%ld\n", m_x + vx*t,m_y + vy*t,time_remaining);
        m_x = m_x + vx*t;
        m_y = m_y + vy*t;
        time_remaining-=t;
    }
    else if(state==MOVE && t>=time_remaining)
    {
        //printf("mx=%f my=%f newx:%f,newy:%f tr:%ld\n",m_x,m_y, m_x + vx*time_remaining,m_y + vy*time_remaining,time_remaining);
        m_x = m_x + vx*time_remaining;
        m_y = m_y + vy*time_remaining;
        state=QUIET;

        time_remaining=0;
        m_row = m_destinationRow;
        m_column = m_destinationColumn;
        eatFood();
        objectiveCompleted();
    }
}

void PacMan::eatFood(){
    m_map->eatFood(m_row,m_column);
}

bool PacMan::objectiveCompleted(){
    if(m_map->allFoodEated()){
        return true;
    }
    return false;
}

void PacMan::draw()
{
    glColor3f(0.1,0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2i(m_x-m_sizeX,m_y-m_sizeY);
    glVertex2i(m_x+m_sizeX,m_y-m_sizeY);
    glVertex2i(m_x+m_sizeX,m_y+m_sizeY);
    glVertex2i(m_x-m_sizeX,m_y+m_sizeY);
    glEnd();
}
