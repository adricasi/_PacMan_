#include "Map.h"

void MapClass::eatFood(int row, int column){
    m_map[row][column].eatFood();
}

bool MapClass::allFoodEated(){
    for(int row=0; row<m_rows;row++){
        for(int column=0; column<m_columns; column++){
            Cell cell = m_map[row][column];
            if(cell.get_value()==CORRIDOR && m_map[row][column].haveFood() && !isInHomeRange(cell)){
                return false;
            }
        }
    }
    return true;
}

Cell MapClass::chooseRandomCellHome(){
    // Return all the cells corridors of the home

    Cell homeCells[HOMEROWS*HOMECOLUMNS];
    int homeCellsSize = 0;

    //Check all home cells
    for(int iHomeRow=0; iHomeRow<HOMEROWS; iHomeRow++){
        for(int iHomeColumn=0; iHomeColumn<HOMECOLUMNS; iHomeColumn++){
            int row = m_initialCellHome.get_row() + iHomeRow;
            int column = m_initialCellHome.get_column() + iHomeColumn;
            Cell homeCell = m_map[row][column];

            if(homeCell.get_value() == CORRIDOR && homeCell.get_row() != m_initialCellHome.get_row()){
                homeCells[homeCellsSize] = homeCell;
                homeCellsSize++;
            }
        }
    }

    int random=randomRange(0,homeCellsSize-1);
    return homeCells[random];
}