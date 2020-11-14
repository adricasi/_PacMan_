#include "../C_Stack/Stack.h"

#ifndef __MAP_H
#define __MAP_H

class MapClass{
    
  private:
    //Variables
    int m_rows, m_columns;

    int m_cellsToVisit;
    bool m_breackWallToConnect = false;
    
    Cell** m_map;
    Cell m_currentCell;
    Cell m_initialCellHome;
    Stack m_stack;

    // Home definition
    int home[HOMEROWS][HOMECOLUMNS] = {{WALL,WALL,WALL,CORRIDOR},
                              {WALL,CORRIDOR,CORRIDOR,CORRIDOR},
                              {WALL,CORRIDOR,CORRIDOR,CORRIDOR},
                              {WALL,CORRIDOR,CORRIDOR,CORRIDOR},
                              {WALL,WALL,WALL,WALL}};

  public:
    //Constructor
    MapClass(int rows, int columns,int height, int width);    

    //-------Main Functions-----------------------------
    void createMap();
    void printMap();
    int getValue(int row, int column);
    void freeMap();
    void drawMap();
    bool availableCell(int row, int column, int neighbour);
    
    //-------Map construction----------------------------
    void initMap();
    int randomRange(int min, int max);
    void visit(Cell cell);
    
    void generateRandomMap();

    Cell checkNeighbours();
    void removeWalls(Cell nextCell);
    void removeWallToSecondConnection();
    bool isInHomeRange(Cell cell);
    bool isAConnection(Cell cell, int neighbour);

    //-------Home construction----------------------------
    void createHome();
    void connectHome();
    void visitHomeCell(int row, int column,int value);
    void findcorridor(Cell homeDoor);

    //---------MapClass Game-------------------------------
    Cell chooseRandomCellHome();
    void eatFood(int row, int column);
    bool allFoodEated();

    //---------get/set-------------------------------------
    Cell getCell(Cell cell){
      return m_map[cell.get_row()][cell.get_column()];
    }

    bool isPar(int number){
      return number%2 == 0;
    }

    int get_numRows(){
      return m_rows;
    }

    int get_numColumns(){
      return m_columns;
    }

};

#endif

