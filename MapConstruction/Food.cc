#include "MapClass.h"
#include <stdio.h>
#include <GL/glut.h>
#include "../CommonFunctions/CommonFunctionsC++.h"

void Food::drawFood(){
    float red = 0.8;
    float green = 0.6;
    float blue = 0.9;
    draw_square(m_x, m_y, m_z, m_sizeX, m_sizeY, m_sizeZ, red, green, blue);

}
