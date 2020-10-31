#include "CommonFunctionsC++.h"
#include <stdio.h>
#include <stdbool.h>

float get_cellPositonX(int column, int maxColumns, int WIDTH){
    float x = (column+0.5)*WIDTH/maxColumns-WIDTH*0.6;
    return x;    
}

float get_cellPositonY(int row, int maxRows, int HEIGHT){
    int inversRow = maxRows-1 - row;
    float y = (inversRow+0.5)*HEIGHT/maxRows-HEIGHT*0.6;                    
    return y;
}

float get_cellSizeX(int column, int maxColumns, int WIDTH){
    float sizeX = ((column+1)*WIDTH/maxColumns-column*WIDTH/maxColumns)/2.0;
    return sizeX;
}

float get_cellSizeY(int row, int maxRows, int HEIGHT){
    int inversRow = maxRows-1 - row;
    float sizeY = ((inversRow+1)*HEIGHT/maxRows-inversRow*HEIGHT/maxRows)/2.0;
    return sizeY;
}
