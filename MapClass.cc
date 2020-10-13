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

//-------------------------------------------------------------------------

void MapClass::initMap(){
    for(int row=0; row<m_rows; row++){
        for(int column=0; column<m_columns; column++){
                //Initialize cells
                m_map[row][column].initCell(m_rows,m_columns,row,column);
                if(!m_map[row][column].get_visited()){
                    m_cellsToVisit = m_cellsToVisit +1;
                }
        }
    }
}

int MapClass::randomRange(int min, int max){
    //returns a random number between min and max including min and max
    return rand() % (max - min + 1) + min;
}

void MapClass::createHome(){
    // Create home in the map
    for(int iHomeRow=0; iHomeRow<HOMEROWS; iHomeRow++){
        for(int iHomeColumn=0; iHomeColumn<HOMECOLUMNS; iHomeColumn++){
            int row = m_initialCellHome.get_row() + iHomeRow;
            int column = m_initialCellHome.get_column() + iHomeColumn;
            visitHomeCell(row,column,home[iHomeRow][iHomeColumn]);
        }
    }
}

void MapClass::visitHomeCell(int row, int column, int value){
    //Visit the home cells
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

    //visit right map part
    m_map[cell.get_row()][m_columns-1-cell.get_column()].visit();

    //visit midle map part when in the middle we have a wall when m_columns/2 is a par number, this column is a wall
    if(!isPar(cell.get_row()) && isPar(m_columns/2) && cell.get_column()==(m_columns/2)-1){
        m_map[cell.get_row()][m_columns/2].visit();
    }
}

//---------------Generate Random Map -------------------------------------------------------------

void MapClass::generateRandomMap(){   
    while(m_cellsToVisit > 0){
        visit(m_currentCell);

        //Step1 - get an unvisited neighbour
        Cell nextCell = checkNeighbours();
        if(!nextCell.equal(m_currentCell)){
            //Exist an unvisited neighbour
            //Step2 - Save the current cell
            m_stack.push(m_currentCell);
            //Step3 - remove the wall between cells
            removeWalls(nextCell);
            //Step4 - visit next cell
            m_currentCell = getCell(nextCell);
        }else if(m_stack.get_top() > 0){
            //If all neighbours have been visited go to the previous cell
            m_currentCell = m_stack.pop();
        }       
    }
}

Cell MapClass::checkNeighbours(){
    // Return an unvisited neighbour

    Cell neighbours[4];
    int neighbourSize = 0;
    neighbour neighbourTop = m_currentCell.get_neighbour(TOP);
    neighbour neighbourRight = m_currentCell.get_neighbour(RIGHT);
    neighbour neighbourBot = m_currentCell.get_neighbour(BOT);
    neighbour neighbourLeft = m_currentCell.get_neighbour(LEFT);

    //Get all the unvisited neighbours
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
        // Return a random unvisited neighbour
        m_breackWallToConnect = true;
        int random=randomRange(0,neighbourSize-1);
        return neighbours[random];
    }else{
        if(m_breackWallToConnect){
            //All the neighbours of the cell have been visited, so we have to remove a wall to establish another connection with a visited neighbour
            //In this way, all the corridors will have at least two corridors connections. This ensure that all corridors have an entrance and exit
            removeWallToSecondConnection();
            m_breackWallToConnect = false;
        }
        return m_currentCell;
    }
}

void MapClass::removeWalls(Cell nextCell){
    //Remove the wall to make the connection with the neighbour to visit

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

void MapClass::removeWallToSecondConnection(){
    //Remove a Wall to make a connection with other visited cell

    Cell top = m_map[m_currentCell.get_row()-1][m_currentCell.get_column()];
    Cell right = m_map[m_currentCell.get_row()][m_currentCell.get_column()+1];
    Cell bot = m_map[m_currentCell.get_row()+1][m_currentCell.get_column()];
    Cell left = m_map[m_currentCell.get_row()][m_currentCell.get_column()-1];

    Cell walls[4];
    int wallsSize = 0;

    if(top.get_value()==WALL && top.get_row()>0 && !isInHomeRange(top) && isAConnection(top,TOP)){
        walls[wallsSize] = top;
        wallsSize = wallsSize +1;
    }
    if(right.get_value()==WALL && right.get_column()<m_columns/2 && !isInHomeRange(right) && isAConnection(right,RIGHT)){
        walls[wallsSize] = right;
        wallsSize = wallsSize +1;
    }
    if(bot.get_value()==WALL && bot.get_row()<m_rows-1 && !isInHomeRange(bot) && isAConnection(bot,BOT)){
        walls[wallsSize] = bot;
        wallsSize = wallsSize +1;
    }
    if(left.get_value()==WALL && left.get_column()>0 && !isInHomeRange(left) && isAConnection(left,LEFT)){
        walls[wallsSize] = left;
        wallsSize = wallsSize +1;
    }

    if(wallsSize > 0){
        // remove a random wall
        m_breackWallToConnect = true;
        int random=randomRange(0,wallsSize-1);
        visit(walls[random]);
    }
}

bool MapClass::isInHomeRange(Cell cell){
    int row = cell.get_row();
    int column = cell.get_column();
    int homeRow = m_initialCellHome.get_row();
    int homeColumn = m_initialCellHome.get_column();

    if(row>=homeRow && row<homeRow+HOMEROWS && column>=homeColumn && column<homeColumn+HOMECOLUMNS){
        return true;
    }
    return false;
}

bool MapClass::isAConnection(Cell cell, int neighbour){
    int row = cell.get_row();
    int column = cell.get_column();
    int value;

    if(neighbour == TOP){
        Cell top = m_map[row-1][column];
        value = top.get_value();
    }if(neighbour == RIGHT){
        Cell right = m_map[row][column+1];
        value = right.get_value();
    }if(neighbour == BOT){
        Cell bot = m_map[row+1][column];
        value = bot.get_value();
    }if(neighbour == LEFT){
        Cell left = m_map[row][column-1];
        value = left.get_value();
    }

    if(value == CORRIDOR){
        return true;
    }
    return false;
}