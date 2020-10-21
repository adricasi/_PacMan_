#include "MapClass.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

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

void MapClass::drawMap(int WIDTH, int HEIGHT){
    for(int column=0;column<m_columns;column++){
        for(int row=0;row<m_rows;row++){
            Cell cell = m_map[row][column];
            if( cell.get_value() == CORRIDOR ) {
                float x = get_cellPositonX(column, m_columns,WIDTH);
                float y = get_cellPositonY(row, m_rows, HEIGHT);
                   
                m_map[row][column].set_position(x, y);

                float sizeX = get_cellSizeX(column, m_columns,WIDTH);
                float sizeY = get_cellSizeY(row, m_rows, HEIGHT);
                m_map[row][column].set_size(sizeX,sizeY);

                m_map[row][column].drawCell(isInHomeRange(cell));
            }
        }
    }
}


bool MapClass::availableCell(int row, int column, int neighbour){
    int value;
    bool homeRange;
    if(neighbour == TOP){
        Cell top = m_map[row-1][column];
        value = top.get_value();
        homeRange = isInHomeRange(top);

    }if(neighbour == RIGHT){
        Cell right = m_map[row][column+1];
        value = right.get_value();
        homeRange = isInHomeRange(right);

    }if(neighbour == BOT){
        Cell bot = m_map[row+1][column];
        value = bot.get_value();
        homeRange = isInHomeRange(bot);

    }if(neighbour == LEFT){
        Cell left = m_map[row][column-1];
        value = left.get_value();
        homeRange = isInHomeRange(left);
    }
    return !homeRange && value==CORRIDOR;
}