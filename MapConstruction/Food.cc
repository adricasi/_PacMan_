#include "MapClass.h"
#include <stdio.h>
#include <GL/glut.h>

void Food::drawFood(){
    glColor3f(0.5,0.2,0.9);
    glBegin(GL_QUADS);

    glVertex2i(m_x-m_sizeX,m_y-m_sizeY); 
    glVertex2i(m_x+m_sizeX,m_y-m_sizeY); 
    glVertex2i(m_x+m_sizeX,m_y+m_sizeY); 
    glVertex2i(m_x-m_sizeX,m_y+m_sizeY);

    glEnd();
}

void Food::deleteFood(){
    glColor3f(0.8,0.8,0.8);
}