#include "../C_Food/Food.h"

#ifndef __CELL_H
#define __CELL_H

struct neighbour{
  bool exists;
  int row;
  int column;
};

class Cell{
  private:
    //Variables
    float m_x, m_y, m_z;   //-- Draw position
    float m_sizeX,m_sizeY,m_sizeZ;
    int m_row, m_column; //-- Cell position
    int m_value;
    bool m_visited;
    Food m_food;
    
    neighbour cell_path_top;
    neighbour cell_path_right;
    neighbour cell_path_bot;
    neighbour cell_path_left;

  public:
    void drawCell(bool isHomeRange, int maxRows, int maxColumns);
    void drawFood(bool isHomeRange, int maxRows, int maxColumns);
    void initCell(int totalRows, int totalColumns, int cellRow, int cellColumn);
    void defineNeighbour(int totalRows, int totalColumns, int neighbourRow, int neighbourColumn, int neighbour);
    void visit();
    void visitHomeCell(int value);

    //-----------------------------------------

    void eatFood();
    bool haveFood();

    // get/set----------------------------------
    void set_position(float x,float y,float z);
    void set_size(float sizeX, float sizeY, float sizeZ);
    void set_row(int row);
    void set_column(int column);
    void set_value(int value);
    void set_visited(bool visited);

    float get_position_x();
    float get_position_y();
    float get_size_x();
    float get_size_y();
    int get_row();
    int get_column();
    int get_value();
    bool get_visited();
    neighbour get_neighbour(int neighbour);

    bool equal(Cell cell);
 
    bool isPar(int number){
    return number%2 == 0;
    }
};

#endif