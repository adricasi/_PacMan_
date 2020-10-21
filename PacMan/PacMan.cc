
#include "PacMan.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdio.h>
#include <GL/glut.h>

PacMan::PacMan(int maxRows, int maxColumns, int height, int width)
{
    m_maxRows = maxRows;
    m_maxColumns = maxColumns;
    m_height = height;
    m_width = width;
    state=QUIET;
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

        float destination_x = get_cellPositonX(destination_column,m_maxColumns,m_width);
        float destination_y = get_cellPositonY(destination_row,m_maxRows,m_height);

        printf("dr:%d, dc:%d, dx: %f, dy: %f| x:%f y:%f\n",destination_row,destination_column, destination_x,destination_y,m_x,m_y);

        vx = (destination_x - m_x)/duration;
        vy = (destination_y - m_y)/duration;
        printf("vx:%f vy:%f\n",vx,vy);

        state=MOVE;
        
        time_remaining=duration;
    }
}

void PacMan::integrate(long t)
{
    
    if(state==MOVE && t<time_remaining)
    {
        printf("t:%ld\n",t);
        printf("newx:%f,newy:%f tr:%ld\n", m_x + vx*t,m_y + vy*t,time_remaining);
        m_x = m_x + vx*t;
        m_y = m_y + vy*t;
        time_remaining-=t;
    }
    else if(state==MOVE && t>=time_remaining)
    {
        printf("mx=%f my=%f newx:%f,newy:%f tr:%ld\n",m_x,m_y, m_x + vx*time_remaining,m_y + vy*time_remaining,time_remaining);
        m_x = m_x + vx*time_remaining;
        m_y = m_y + vy*time_remaining;
        state=QUIET;

        time_remaining=0;
        m_row = m_destinationRow;
        m_column = m_destinationColumn;
    }
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
