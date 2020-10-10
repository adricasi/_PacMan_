#include "MapClass.h"
#include <stack>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//-----------------------------------------------

time_t t;



//Constructor
MapClass::MapClass(int rows, int columns){
    m_rows = rows;
    m_columns = columns;

    m_initialCellHome.set_row( m_rows/2 - (1 - HOMEROWS%2 + HOMEROWS/2));
    m_initialCellHome.set_column(m_columns/2 - (1 - HOMECOLUMNS%2 + HOMECOLUMNS/2));


    //Define m_map size
    m_map = (Cell **)malloc(rows * sizeof(Cell *)); 
    for (int i=0; i<rows; i++){
         m_map[i] = (Cell *)malloc(columns * sizeof(Cell)); 
    }
}

//Public functions
void MapClass::createMap(){
    /* Intializes random number generator */
    srand((unsigned) time(&t));

    initMap();
    defineBordersWalls();
    createHome();
    //Generate random map
    generateRandomMap();

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

//-------------------------------------------------------------------------


void MapClass::initMap(){
    for(int row=0; row<m_rows; row++){
        for(int column=0; column<m_columns; column++){
                m_map[row][column].initCell(m_rows,m_columns,row,column);
        }
    }
}


void MapClass::createHome(){
    for(int iHomeRow=0; iHomeRow<HOMEROWS; iHomeRow++){
        for(int iHomeColumn=0; iHomeColumn<HOMECOLUMNS; iHomeColumn++){
            int row = m_initialCellHome.get_row() + iHomeRow;
            int column = m_initialCellHome.get_column() + iHomeColumn;
            writeCell(row,column,home[iHomeRow][iHomeColumn]);
        }
    }
}

void MapClass::defineBordersWalls(){
    for(int row = 0; row<m_rows; row++){
        int column=0;
        if(row == 0 || row == m_rows-1){
            for(column=0;column<(m_columns/2)+1; column++){
                //writeValue(row,column,WALL);
            }
        }else{
            //writeValue(row,column,WALL);
        }
    }
}

void MapClass::writeCell(int row, int column, int value){
    m_map[row][column].set_value(value);
    m_map[row][column].set_visited(true);
    m_map[row][m_columns-1-column].set_value(value);
    m_map[row][m_columns-1-column].set_visited(true);
}

int MapClass::randomRange(int min, int max){
    return rand() % (max - min + 1) + min;
}


void MapClass::generateRandomMap(){

}

//---------------Cell Class-------------------------------
void Cell::initCell(int rows, int columns, int cellRow, int cellColumn){
    if(cellRow%2 != 0 && cellColumn%2 !=0){
        m_row = cellRow;
        m_column = cellColumn;
        m_value = CORRIDOR;
        m_visited = false;
        
        if(cellRow+2 >= rows){
            cell_path_n[0]=-1;
            cell_path_n[1]=-1;
        }else{
            cell_path_n[0]=cellRow+2;
            cell_path_n[1]=cellColumn;
        }
        
        cell_path_s[0]=cellRow-2;
        cell_path_s[1]=cellColumn;

        cell_path_w[0]=cellRow;
        cell_path_w[1]=cellColumn-2;


        if(cellColumn+2 > columns/2){
            cell_path_e[0]=-1;
            cell_path_e[1]=-1;
        }else{
            cell_path_e[0]=cellRow;
            cell_path_e[1]=cellColumn+2;
        }
        
    }else{
        m_value=WALL;
        m_visited=true; 
    }
}