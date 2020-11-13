#include "MapClass.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdio.h>
#include <GL/glut.h>

void Cell::initCell(int totalRows, int totalColumns, int cellRow, int cellColumn){
    /*
        ----Initialize the cell----
        
        If it is an par cell, it will be treated as a wall, we do not need to visit the cell at the execution of the algorithm
        
        If it is a odd cell it will be treated as a Corridor, we must visit the cell at the exectuion of the algorithm

        The cell must know their neighbours, their neighbours will be the other cells around it that the algorithm must visit.
    */
    m_food.init_food();
    m_row = cellRow;
    m_column = cellColumn;
    m_value = WALL;

    if(!isPar(m_row) && !isPar(m_column) && m_row<totalRows-1 && m_column<=totalColumns/2){
        //Define cells to visit (corridors)
        m_visited = false;
        //Define the neighbour beetween cells to visit
        defineNeighbour(totalRows, totalColumns, m_row-2, m_column, TOP);
        defineNeighbour(totalRows, totalColumns, m_row, m_column+2, RIGHT);
        defineNeighbour(totalRows, totalColumns, m_row+2, m_column, BOT);
        defineNeighbour(totalRows, totalColumns, m_row, m_column-2, LEFT);
    }else{
        //Define walls
        m_visited=true; 
    }
}


void Cell::defineNeighbour(int totalRows, int totalColumns, int neighbourRow, int neighbourColumn, int neighbour){
    //Define the existing neighbours of the cell
    int exists = true;
    if(neighbourRow<0 || neighbourColumn<0 || neighbourRow>=totalRows || neighbourColumn>totalColumns/2){
            exists = false;
    }

    if(neighbour == TOP){
        cell_path_top.row = neighbourRow;
        cell_path_top.column = neighbourColumn;
        cell_path_top.exists = exists;
    }else if(neighbour == RIGHT){
        cell_path_right.column = neighbourColumn;
        cell_path_right.row = neighbourRow;
        cell_path_right.exists = exists;
    }else if(neighbour == BOT){
        cell_path_bot.row = neighbourRow;
        cell_path_bot.column = neighbourColumn;
        cell_path_bot.exists = exists;
    }else if(neighbour == LEFT){
        cell_path_left.column = neighbourColumn;
        cell_path_left.row = neighbourRow;
        cell_path_left.exists = exists;
    }
}

void Cell::visit(){
    m_visited=true;
    m_value=CORRIDOR;
}
void Cell::visitHomeCell(int value){ 
    m_visited=true;
    m_value=value;
}

//Get/Set

void Cell::set_position(float x,float y, float z){
    m_x = x;
    m_y = y;
    m_z = z;
}  
void Cell::set_size(float sizeX, float sizeY, float sizeZ){
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_sizeZ = sizeZ;
}
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
    }else{
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


//-----------------Draw-------------------------------------


void Cell::drawCell(bool isHomeRange){
    float maxTexturePositionX = 1.0;
    float minTexturePositionX = 0.0;
    float maxTexturePositionY = 1.0;
    float minTexturePositionY = 0.0;

    if(m_value == WALL){
        float red = 0.2;
        float green = 0.0;
        float blue = 0.3;

        glEnable(GL_TEXTURE_2D);
        draw_wall(m_x, m_y, m_z, m_sizeX, m_sizeY, m_sizeZ, red, green, blue, maxTexturePositionX, minTexturePositionX, maxTexturePositionY, minTexturePositionY);
        glDisable(GL_TEXTURE_2D);

    }else if(m_value == CORRIDOR){
        drawFood(isHomeRange);
    }

    float red = 1;
    float green = 0.95;
    float blue = 1;

    //Define floor texture
    glEnable(GL_TEXTURE_2D);
    draw_floor(m_x, m_y, m_z, m_sizeX, m_sizeY, m_sizeZ, red, green, blue, maxTexturePositionX, minTexturePositionX, maxTexturePositionY, minTexturePositionY);
    glDisable(GL_TEXTURE_2D);
}

void Cell::eatFood(){
    m_food.set_exist(false);
}

bool Cell::haveFood(){
    return m_food.get_exist();
}

void Cell::drawFood(bool isHomeRange){
    if(!isHomeRange && m_food.get_exist()){
        m_food.set_position(m_x, m_y, m_z);
        m_food.set_size(m_sizeX/2.5, m_sizeY/2.5, m_sizeZ/2.5);
        m_food.drawFood();
    }
}