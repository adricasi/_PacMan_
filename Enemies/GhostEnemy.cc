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

    //------------------------
    int num_columns = m_map->get_numColumns();
    int num_rows = m_map->get_numRows();
    int height = m_map->get_height();
    int width = m_map->get_width();

    float positionX = get_cellPositonX(init_column, num_columns, width);
    float positionY = get_cellPositonY(init_row, num_rows, height);
    float sizeX = get_cellSizeX(init_column, num_columns, width)/2.0;
    float sizeY = get_cellSizeY(init_row, num_rows, height)/2.0;


    set_position(init_row, init_column, positionX, positionY);
    set_size(sizeX, sizeY);   
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