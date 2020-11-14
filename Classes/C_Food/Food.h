#include "../CommonFunctions/CommonFunctions.h"

#ifndef __FOOD_H
#define __FOOD_H

class Food{
  private:
    float m_sizeX,m_sizeY,m_sizeZ;
    float m_x,m_y,m_z;   //-- Draw position
    bool m_exist;
  public:
    void init_food(){
      m_exist = true;
    }

    void drawFood();
    void set_position(int x,int y, int z)
    {
      m_x = x;
      m_y = y;
      m_z = z;
    }
    void set_size(float sizeX, float sizeY, float sizeZ)
    {
      m_sizeX = sizeX;
      m_sizeY = sizeY;
      m_sizeZ = sizeZ;
    }
    void set_exist(bool exist){
      m_exist = exist;
    }
    bool get_exist(){
      return m_exist;
    }
};

#endif