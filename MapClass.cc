#include "MapClass.h"
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

//Public functions
void MapClass::createMap(){
    /* Intializes random number generator */
    srand((unsigned) time(&t));

    initMap();
    //createHome();

    //Generate random map
    m_currentCell = m_map[1][1];
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
                if(!m_map[row][column].get_visited()){
                    m_cellsToVisit = m_cellsToVisit +1;
                }
        }
    }
}

int MapClass::randomRange(int min, int max){
    return rand() % (max - min + 1) + min;
}

void MapClass::visit(Cell cell){
    if(!m_map[cell.get_row()][cell.get_column()].get_visited()){
        m_cellsToVisit = m_cellsToVisit-2;
    }
    m_map[cell.get_row()][cell.get_column()].visit();
    //Write right map part
    m_map[cell.get_row()][m_columns-1-cell.get_column()].visit();
}

//---------------Generate Random Map -------------------------------------------------------------

void MapClass::generateRandomMap(){   
    if(m_cellsToVisit > 0){
        visit(m_currentCell);
        printf("stack top %d \n",m_stack.get_top());
        printf("tovisit %d \n",m_cellsToVisit);

        //Step1
        Cell nextCell = checkNeighbours();
        if(!nextCell.equal(m_currentCell)){
            //Exist a non visited neighbour
            //Step2
            m_stack.push(m_currentCell);
            //Step3
            removeWalls(nextCell);
            //Step4
            m_currentCell = getCell(nextCell);
        }else if(m_stack.get_top() > 0){
            m_currentCell = m_stack.pop();
        }
        generateRandomMap();       
    }
}

Cell MapClass::checkNeighbours(){
    Cell neighbours[4];
    int neighbourSize = 0;
    neighbour neighbourTop = m_currentCell.get_neighbour(TOP);
    neighbour neighbourRight = m_currentCell.get_neighbour(RIGHT);
    neighbour neighbourBot = m_currentCell.get_neighbour(BOT);
    neighbour neighbourLeft = m_currentCell.get_neighbour(LEFT);

    if(neighbourTop.exists){
        Cell top = m_map[neighbourTop.row][neighbourTop.column];
        if(!top.get_visited()){
            neighbours[neighbourSize] = top;
            neighbourSize = neighbourSize +1;
        }
    }
    if(neighbourRight.exists){
        Cell right = m_map[neighbourRight.row][neighbourRight.column];
        if(!right.get_visited()){
            neighbours[neighbourSize] = right;
            neighbourSize = neighbourSize +1;
        }
    }
    if(neighbourBot.exists){
        Cell bot = m_map[neighbourBot.row][neighbourBot.column];
        if(!bot.get_visited()){
            neighbours[neighbourSize] = bot;
            neighbourSize = neighbourSize +1;
        }
    }
    if(neighbourLeft.exists){
        Cell left = m_map[neighbourLeft.row][neighbourLeft.column];
        if(!left.get_visited()){
            neighbours[neighbourSize] = left;
            neighbourSize = neighbourSize +1;
        }
    }
    if(neighbourSize > 0){
        int random=randomRange(0,neighbourSize-1);
        return neighbours[random];
    }else{
        return m_currentCell;
    }
}

void MapClass::removeWalls(Cell nextCell){
    if(m_currentCell.get_neighbour(TOP).row==nextCell.get_row() && m_currentCell.get_neighbour(TOP).column==nextCell.get_column()){
        visit(m_map[m_currentCell.get_row()-1][m_currentCell.get_column()]);
    }
    if(m_currentCell.get_neighbour(RIGHT).row==nextCell.get_row() && m_currentCell.get_neighbour(RIGHT).column==nextCell.get_column()){
        visit(m_map[m_currentCell.get_row()][m_currentCell.get_column()+1]);
    }
    if(m_currentCell.get_neighbour(BOT).row==nextCell.get_row() && m_currentCell.get_neighbour(BOT).column==nextCell.get_column()){
        visit(m_map[m_currentCell.get_row()+1][m_currentCell.get_column()]);
    }
    if(m_currentCell.get_neighbour(LEFT).row==nextCell.get_row() && m_currentCell.get_neighbour(LEFT).column==nextCell.get_column()){
        visit(m_map[m_currentCell.get_row()][m_currentCell.get_column()-1]);
    }
}


//---------------Cell Class-------------------------------
void Cell::initCell(int totalRows, int totalColumns, int cellRow, int cellColumn){
    m_row = cellRow;
    m_column = cellColumn;
    m_value = WALL;

    if(m_row%2 != 0 && m_column%2 !=0){
        //Define corridors
        m_visited = false;
    }else{
        //Define walls
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
    if(cellRow < 0 || cellColumn < 0 || cellRow > totalRows-1 || cellColumn > (totalColumns/2)){
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

void Cell::visit(){
    m_visited=true;
    m_value=CORRIDOR;
}

//--------------------Stack----------------
void Stack::initStack(int maxSize) {
    top = 0;
    m_max_size = maxSize;
    arr_stack = (Cell *)malloc(m_max_size * sizeof(Cell));
}