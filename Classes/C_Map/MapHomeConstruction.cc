
#include "Map.h"

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
    //Find a corridor to connect with the door of the home
    
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