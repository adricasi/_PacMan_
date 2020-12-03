#include "Food.h"


void Food::drawFood(){
    float red = 0.8;
    float green = 0.6;
    float blue = 0.9;
    draw_sphere(m_x, m_y, m_z, m_radius, red, green, blue);
}
