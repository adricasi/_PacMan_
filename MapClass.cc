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

//Public functions//-----------------------------------------------
void MapClass::createMap(){
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    
    initMap();
    createHome();

    m_currentCell = m_map[1][1];
    generateRandomMap();
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
/*
    for(int row=0; row<m_rows; row++){
        for(int column=0; column<m_columns; column++){
            if(m_map[row][column].get_visited()==1){
                printf("%d",m_map[row][column].get_visited());
            }else{
                printf(" ");
            }
        }
        printf("\n");

    }
    printf("\n");

    for(int row=0; row<m_rows; row++){
        for(int column=0; column<m_columns; column++){
            Cell thisC = m_map[row][column];
            neighbour nR = thisC.get_neighbour(RIGHT);
            neighbour nL = thisC.get_neighbour(LEFT);

            //printf("right r: %d c: %d ||", nR.row, nR.column );
            printf("left r: %d c: %d ||", nL.row, nL.column );

        }
    printf("\n");

    }
    printf("\n");*/
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

void MapClass::createHome(){
    for(int iHomeRow=0; iHomeRow<HOMEROWS; iHomeRow++){
        for(int iHomeColumn=0; iHomeColumn<HOMECOLUMNS; iHomeColumn++){
            int row = m_initialCellHome.get_row() + iHomeRow;
            int column = m_initialCellHome.get_column() + iHomeColumn;
            visitHomeCell(row,column,home[iHomeRow][iHomeColumn]);
        }
    }
}

void MapClass::visitHomeCell(int row, int column, int value){
    if(!m_map[row][column].get_visited()){
        m_cellsToVisit = m_cellsToVisit-1;
    }
    m_map[row][column].visitHomeCell(value);
    //Write right map part
    m_map[row][m_columns-1-column].visitHomeCell(value);
}

void MapClass::connectHome(){
    Cell homeDoor = m_initialCellHome;
    homeDoor.set_column(m_initialCellHome.get_column()+3);
    findcorridor(homeDoor);    
}
void MapClass::findcorridor(Cell homeDoor){
    Cell top = m_map[homeDoor.get_row()-1][homeDoor.get_column()];
    Cell left = m_map[homeDoor.get_row()][homeDoor.get_column()-1];
    Cell right = m_map[homeDoor.get_row()][homeDoor.get_column()+1];

    if(top.get_value() == WALL && left.get_value() == WALL && right.get_value() == WALL){
        if(top.get_row()!=0){
            m_map[top.get_row()][top.get_column()].set_value(CORRIDOR);
            findcorridor(top);
        }else if(left.get_column()!=0){
            m_map[left.get_row()][left.get_column()].set_value(CORRIDOR);
            findcorridor(left);
        }
    }
}

void MapClass::visit(Cell cell){
    if(!m_map[cell.get_row()][cell.get_column()].get_visited()){
        m_cellsToVisit = m_cellsToVisit-1;
    }
    
    m_map[cell.get_row()][cell.get_column()].visit();

    //Write right map part
    m_map[cell.get_row()][m_columns-1-cell.get_column()].visit();

    //Write midle map part
    if(cell.get_row()%2!=0 && (m_columns/2)%2==0 && cell.get_column()==(m_columns/2)-1){
        m_map[cell.get_row()][m_columns/2].visit();

    }
}

//---------------Generate Random Map -------------------------------------------------------------

void MapClass::generateRandomMap(){   
    while(m_cellsToVisit > 0){
        visit(m_currentCell);

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