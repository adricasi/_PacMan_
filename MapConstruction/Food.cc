#include "MapClass.h"
#include <stdio.h>
#include <GL/glut.h>

void Food::drawFood(){
    glColor3f(0.7,0.4,0.8);
    glBegin(GL_QUADS);

    glVertex2i(m_x-m_sizeX,m_y-m_sizeY); 
    glVertex2i(m_x+m_sizeX,m_y-m_sizeY); 
    glVertex2i(m_x+m_sizeX,m_y+m_sizeY); 
    glVertex2i(m_x-m_sizeX,m_y+m_sizeY);

    glEnd();
}
