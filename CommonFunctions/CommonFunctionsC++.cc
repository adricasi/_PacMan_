#include "CommonFunctionsC++.h"
#include <stdio.h>
#include <stdbool.h>

float get_cellPositonX(int column, int maxColumns, int WIDTH){
    float x = ((column+0.5)*WIDTH/maxColumns)-WIDTH/2;
    return x;    
}

float get_cellPositonY(int row, int maxRows, int HEIGHT){
    float y = 0;                    
    return y;
}

float get_cellPositonZ(int row, int maxRows, int HEIGHT){
    float z = ((row+0.5)*HEIGHT/maxRows)-HEIGHT/2;                    
    return z;
}

//------------------------------------------------------------------

float get_cellSizeX(int column, int maxColumns, int WIDTH){
    float sizeX = ((column+1)*WIDTH/maxColumns-column*WIDTH/maxColumns)/2.0;
    return sizeX;
}

float get_cellSizeY(int row, int maxRows, int HEIGHT){
    float sizeY = ((row+1)*HEIGHT/maxRows-row*HEIGHT/maxRows)/2.0;
    return sizeY;
}

float get_cellSizeZ(int row, int maxRows, int HEIGHT){
    float sizeZ = ((row+1)*HEIGHT/maxRows-row*HEIGHT/maxRows)/2.0;
    return sizeZ;
}
