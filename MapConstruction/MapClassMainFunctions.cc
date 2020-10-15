#include "MapClass.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t t;

//Constructor
MapClass::MapClass(int rows, int columns){
    m_rows = rows;
    m_columns = columns;
    m_cellsToVisit = 0;

    m_initialCellHome.set_row( m_rows/2 - (1 - HOMEROWS%2 + HOMEROWS/2));
    m_initialCellHome.set_column(m_columns/2 - (1 - HOMECOLUMNS%2 + HOMECOLUMNS/2));

    m_stack.initStack(m_rows*m_columns);

    //Define m_map size
    m_map = (Cell **)malloc(rows * sizeof(Cell *)); 
    for (int i=0; i<rows; i++){
         m_map[i] = (Cell *)malloc(columns * sizeof(Cell)); 
    }
}

//Main functions//-----------------------------------------------
void MapClass::createMap(){
    // Intializes random number generator
    srand((unsigned) time(&t));
    
    // initialize map
    initMap();

    createHome();

    m_currentCell = m_map[INITIAL_ROW][INITIAL_COLUMN];    
    generateRandomMap();

    //Create a second connection in the initial position
    m_currentCell = m_map[INITIAL_ROW][INITIAL_COLUMN]; 
    removeWallToSecondConnection();
    
    //Ensure that the home door is connected with a corridor
    connectHome();
}

void MapClass::printMap(){
    printf("MAP:\n");
    for(int row=0; row<m_rows; row++){
        for(int column=0; column<m_columns; column++){
            if(m_map[row][column].get_value()==0){
                printf("%d",m_map[row][column].get_value());
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int MapClass::getValue(int row, int column){
    return m_map[row][column].get_value();
}

void MapClass::freeMap(){
    free(m_map);
    m_map = NULL;
    m_stack.freeStack();
}