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
    //createHome();
    //Generate random map
    //generateRandomMap();

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
    /*
    for(int row=0; row<m_rows; row++){
        for(int column=0; column<m_columns; column++){
            neighbour neighbour = m_map[row][column].get_neighbour(RIGHT);
            printf(" exist:%d r:%d c:%d ||",neighbour.exists,neighbour.row,neighbour.column);
        }
        printf("\n");
    }
    printf("\n");
    */
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
void Cell::initCell(int totalRows, int totalColumns, int cellRow, int cellColumn){
    m_row = cellRow;
    m_column = cellColumn;

    if(m_row%2 != 0 && m_column%2 !=0){
        //Define corridors
        m_value = CORRIDOR;
        m_visited = false;
    }else{
        //Define walls
        m_value=WALL;
        m_visited=true; 
    }

    //Define neightbours
    defineNeighbour(totalRows, totalColumns, m_row-2, m_column, TOP);
    defineNeighbour(totalRows, totalColumns, m_row, m_column+2, RIGHT);
    defineNeighbour(totalRows, totalColumns, m_row+2, m_column, BOT);
    defineNeighbour(totalRows, totalColumns, m_row, m_column-2, LEFT);
}

void Cell::defineNeighbour(int totalRows, int totalColumns, int cellRow, int cellColumn, int neighbour){
    int exists = true;
    if(cellRow < 0 || cellColumn < 0 || cellRow > totalRows-1 || cellColumn > totalColumns/2){
        exists = false;
    }

    if(neighbour == TOP){
        cell_path_top.row = cellRow;
        cell_path_top.column = cellColumn;
        cell_path_top.exists = exists;
    }else if(neighbour == RIGHT){
        cell_path_right.row = cellRow;
        cell_path_right.column = cellColumn;
        cell_path_right.exists = exists;
    }else if(neighbour == BOT){
        cell_path_bot.row = cellRow;
        cell_path_bot.column = cellColumn;
        cell_path_bot.exists = exists;
    }else if(neighbour == LEFT){
        cell_path_left.row = cellRow;
        cell_path_left.column = cellColumn;
        cell_path_left.exists = exists;
    }
}