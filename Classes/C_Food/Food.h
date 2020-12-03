#include "../CommonFunctions/CommonFunctions.h"

#ifndef __FOOD_H
#define __FOOD_H

class Food{
  private:
    float m_radius;
    float m_x,m_y,m_z;   //-- Draw position
    bool m_exist;
    float m_sizeDivision;
  public:
    void init_food(){
      m_exist = true;
      m_sizeDivision = 2.5;
    }

    void drawFood();
    void set_position(int x,int y, int z)
    {
      m_x = x;
      m_y = y;
      m_z = z;
    }
    void set_radius(float radius){
        m_radius = radius;
    }
    void set_exist(bool exist){
      m_exist = exist;
    }
    bool get_exist(){
      return m_exist;
    }
    float get_sizeDivision(){
      return m_sizeDivision;
    }
};

#endif