#include "Food.h"


void Food::drawFood(){
    float red = 0.8;
    float green = 0.6;
    float blue = 0.9;
    float maxTexturePositionX = 1.0;
    float minTexturePositionX = 0.0;
    float maxTexturePositionY = 1.0;
    float minTexturePositionY = 0.0;
    
    draw_square(m_x, m_y, m_z, m_sizeX, m_sizeY, m_sizeZ, red, green, blue, maxTexturePositionX, minTexturePositionX, maxTexturePositionY, minTexturePositionY);
}
