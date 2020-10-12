#include "MapClass.h"

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
    if(cellRow < 0 || cellColumn < 0 || cellRow > totalRows-1 || cellColumn > (totalColumns/2)+1){
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

//Get/Set
void Cell::set_row(int row){
    m_row = row;
}
void Cell::set_column(int column){
    m_column = column;
}
void Cell::set_value(int value){
    m_value = value;
}
void Cell::set_visited(bool visited){
    m_visited = visited;
}

int Cell::get_row(){
    return m_row;
}
int Cell::get_column(){
    return m_column;
}
int Cell::get_value(){
    return m_value;
}
bool Cell::get_visited(){
    return m_visited;
}

neighbour Cell::get_neighbour(int neighbour){
    if(neighbour == TOP){
        return cell_path_top;
    }else if(neighbour == RIGHT){
        return cell_path_right;
    }else if(neighbour == BOT){
        return cell_path_bot;
    }else if(neighbour == LEFT){
        return cell_path_left;
    }
}

bool Cell::equal(Cell cell){
    if(m_row == cell.get_row() && m_column == cell.get_column()){
        return true;
    }else{
        return false;
    }
}
